package org.HCPAtools.Hadoop;

import java.io.*;
import java.util.*;
import java.net.URI;
import java.nio.charset.Charset;

import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.*;
import org.apache.hadoop.filecache.DistributedCache;

public class DiseaseApplication
{

    public static class Map extends Mapper<LongWritable, Text, Text, Text>
    {
	
	  String[] IDs = null;
	  int codonID = 1;
	  Text outputKey = null;
	  Text outputValue = null;
	  
	  Path[] localFiles;
	  
	  HashMap<String, ArrayList<char[]>> GenesIndex = null;
	  String currentGene = null;
	  ArrayList<char[]> currentRefSeq = null;
	  
	  @Override
	  public void setup(Context context) throws IOException, InterruptedException
	  {
	
		long currFileOffSet = 0;
		GenesIndex = new HashMap<String, ArrayList<char[]>>();
		outputKey = new Text();
		outputValue = new Text();

		localFiles = DistributedCache.getLocalCacheFiles(context.getConfiguration());
		FileSystem fs = FileSystem.getLocal(context.getConfiguration());
		FSDataInputStream in = null;

		ArrayList<char[]> AuxRefSeq = new ArrayList<char[]>();
		byte[] buffer = new byte[3];
	
		int EOF = 2;
	
		String geneFilePath = null;
		String geneName = null;
		byte[] eofBuffer = new byte[2];

		for(int i=0; i<localFiles.length; i++) 
		{
			geneFilePath = localFiles[i].getName();
			
			if(localFiles[i].toString().indexOf("generef/") != -1)
			{
				geneName = geneFilePath.substring(0, geneFilePath.length()-9);
				
				try
				{
					in = fs.open(localFiles[i]);
					while(EOF == 2)
					{
						in.read(currFileOffSet,buffer,0,3);
						AuxRefSeq.add((new String(buffer, "UTF-8")).toCharArray());
						
						currFileOffSet += 4;
						EOF = in.read(currFileOffSet, eofBuffer, 0, 2);
					}
				} 
				catch(IOException e)
				{
					throw new IOException("EOF: " + EOF + 
					"\neofBuffer: " + new String(eofBuffer, "UTF-8") + 
					"\ngeneFilePath: " + geneFilePath +
					"\ncurrFileOffSet: " + currFileOffSet +
					"\ngeneName: " + geneName, e);
				}
				finally 
				{
					IOUtils.closeStream(in);
				}
				
				GenesIndex.put(geneName, AuxRefSeq);
				AuxRefSeq = new ArrayList<char[]>();
				EOF = 2;
				currFileOffSet = 0;
			}
		}

	  }
	  
	  @Override
	  public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
	  {		
	
		codonID = 1;
		StringTokenizer tokenizer = new StringTokenizer(value.toString());
		
		if(tokenizer.hasMoreTokens()) // gera um array com geneID e patientID
		{ 
			IDs = tokenizer.nextToken().split(">")[1].split("_");
		}
		
		if(!IDs[0].equals(currentGene))
		{
			currentRefSeq = GenesIndex.get(IDs[0]);
			currentGene = IDs[0];
			outputKey.set(IDs[0]);
		}
		
		char[] patSeq = null;
		char[] refSeq = null;
		
		while (tokenizer.hasMoreTokens())
		{
			patSeq = tokenizer.nextToken().toCharArray();			
			refSeq = currentRefSeq.get(codonID - 1);
			
			if ('n'!=patSeq[0] && 'n'!=patSeq[1] && 'n'!= patSeq[2])
			{
				if (patSeq[0] != refSeq[0])
				{
					
					if (patSeq[2] != refSeq[2])
					{
						outputValue.set(IDs[1]+"_"+codonID+"3_"+new String(refSeq)+"_"+new String(patSeq));
						context.write(outputKey, outputValue);
					}
					
					outputValue.set(IDs[1]+"_"+codonID+"1_"+new String(refSeq)+"_"+new String(patSeq));
					context.write(outputKey, outputValue);
				}
				else if (patSeq[1] != refSeq[1])
				{
					outputValue.set(IDs[1]+"_"+codonID+"2_"+new String(refSeq)+"_"+new String(patSeq));
					context.write(outputKey, outputValue);
				}
				else if (patSeq[2] != refSeq[2])
				{
					outputValue.set(IDs[1]+"_"+codonID+"3_"+new String(refSeq)+"_"+new String(patSeq));
					context.write(outputKey, outputValue);
				}
			}
			++codonID;
		}
	  }
    }

    public static class Reduce extends Reducer<Text, Text, Text, Text> 
    {
	
	  Path[] localFiles;	  
	  HashMap<String, HashMap<String, String>> EnsemblDB = null;
	  HashMap<String, String> EnsemblDBHash = null;
	  ArrayList<String> currentGeneDB = null;
	  Text outputValue = null;
	  String codon_number = null;
	  String currValue = null;
	  Iterator<Text> valuesList = null;
	  
	  @Override
	  public void setup(Context context) throws IOException, InterruptedException 
	  {
		EnsemblDB = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> AuxRefSeq = new HashMap<String, String>();
		outputValue = new Text();

		localFiles = DistributedCache.getLocalCacheFiles(context.getConfiguration());
		
		String geneFilePath = null;
		String geneName = null;
		
		InputStream    fis;
		BufferedReader br;
		String         line;
		
		for(int i=0; i<localFiles.length; i++)
		{
			geneFilePath = localFiles[i].getName();
			
			if(localFiles[i].toString().indexOf("db/") != -1){
				geneName = geneFilePath.substring(0, geneFilePath.length()-4);
				
				fis = new FileInputStream(localFiles[i].toString());
				br = new BufferedReader(new InputStreamReader(fis));
				
				while ((line = br.readLine()) != null) 
				{
					AuxRefSeq.put(line.split("\\s+")[0]+line.split("\\s+")[1], line);
				}
				
				br.close();
				br = null;
				fis = null;
				
				EnsemblDB.put(geneName, AuxRefSeq);
				AuxRefSeq = new HashMap<String, String>();
			}
		}
	  }
	  
	  @Override
      public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException
      {
		
		EnsemblDBHash = EnsemblDB.get(key.toString());
		
		valuesList = values.iterator();
		
        while (valuesList.hasNext())
        {
        
          currValue = valuesList.next().toString();
		  codon_number = currValue.split("_")[1];
		  
		  if(EnsemblDBHash.get(codon_number) != null)
		  {
			outputValue.set(currValue + " - DB data: " + EnsemblDBHash.get(codon_number));
			context.write(key, outputValue);
		  }
        }
      }
    }

    public static void main(String[] args) throws Exception 
    {
	
	  Configuration conf = new Configuration();
	  
	  Job job = new Job(conf, "DiseaseApplication");
	  
	  DistributedCache.addCacheFile(new Path("/home/user/generef/ABCB11_GENE.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/generef/ABCB4_GENE.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/generef/ATP8B1_GENE.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/generef/JAG1_GENE.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/generef/SERPINA1_GENE.txt").toUri(), job.getConfiguration());
	  
	  DistributedCache.addCacheFile(new Path("/home/user/db/ABCB11.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/db/ABCB4.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/db/ATP8B1.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/db/JAG1.txt").toUri(), job.getConfiguration());
	  DistributedCache.addCacheFile(new Path("/home/user/db/SERPINA1.txt").toUri(), job.getConfiguration());
	  
	  job.setJarByClass(DiseaseApplication.class);
	  job.setMapperClass(Map.class);
	  job.setCombinerClass(Reduce.class);
	  job.setReducerClass(Reduce.class);
	  job.setOutputKeyClass(Text.class);
	  job.setOutputValueClass(Text.class);
	  
      FileInputFormat.setInputPaths(job, new Path(args[0]));
      FileOutputFormat.setOutputPath(job, new Path(args[1]));

	  System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}