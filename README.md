########## Instalação de cada nó do Hadoop (11 passos) ##########

#1 Download SDK8 e Hadoop 1.0.4 (Jogue na pasta Downloads estes files)

http://download.oracle.com/otn-pub/java/jdk/8u5-b13/jdk-8u5-linux-x64.tar.gz?AuthParam=1399867027_aa709da0c839c4e6dc89f28712f0ccb2
http://archive.apache.org/dist/hadoop/core/hadoop-1.0.4/hadoop-1.0.4.tar.gz

#2 Tire a permissão dos arquivos

cd Downloads/

chmod 775 -Rf hadoop-1.0.4.tar.gz
chmod 775 -Rf jdk-8u5-linux-x64.tar.gz

#3 Extraia os arquivos compactados

tar xvf hadoop-1.0.4.tar.gz
tar xvf jdk-8u5-linux-x64.tar.gz

#4 Instalacão e configuracão do SSH (Liberacão do localhost)

cd
sudo apt-get install openssh-server
ssh-keygen -t rsa -P ""
cat $HOME/.ssh/id_rsa.pub >> $HOME/.ssh/authorized_keys

#5 Reboote a VM e teste se o SSH loga sem a senha

sudo reboot
ssh localhost

#6 Migre o JDK e o Hadoop para seus diretórios corretos.

cd Downloads/
sudo mv hadoop-1.0.4 ~/hadoop
sudo mv jdk-8u5-linux-x64 /opt/java
cd ..
chmod 775 -Rf hadoop

#7 Edite o bashrc do usuário local (Troque user pelo nome do usuário)

gedit .bashrc

export JAVA_HOME=/opt/java
export JRE_HOME=/opt/java/jre
export HADOOP_PREFIX=/home/user/hadoop

unalias fs &> /dev/null
alias fs="hadoop fs"
unalias hls &> /dev/null
alias hls="fs -ls"

lzohead () 
{
    hadoop fs -cat $1 | lzop -dc | head -1000 | less
}

export PATH=$PATH:/opt/java/bin:/opt/java/jre/bin
export PATH=$PATH:$HADOOP_PREFIX/bin
export PATH=$PATH:$HADOOP_PREFIX/lib

source .bashrc

#7 Edite o arquivo hadoop-env.sh e troque a variável de ambiente JAVA_HOME

gedit hadoop/conf/hadoop-env.sh
export JAVA_HOME=/opt/java

#8 Pasta temporária no Hadoop onde o HDFS irá ser montado

mkdir hadoop/tmp
chmod 775 -Rf hadoop/tmp

#9 Edite o arquivo core-site.xml entre as tags <configuration> coloque o conteudo abaixo. Edite a linha <value> trocando user pelo nome do usuário.

gedit conf/core-site.xml

<property>
  <name>hadoop.tmp.dir</name>
  <value>/home/user/hadoop/tmp</value>
  <description>A base for other temporary directories.</description>
</property>


<property>
  <name>fs.default.name</name>
  <value>hdfs://localhost:54310</value>
  <description>The name of the default file system.  A URI whose
  scheme and authority determine the FileSystem implementation.  The
  uri's scheme determines the config property (fs.SCHEME.impl) naming
  the FileSystem implementation class.  The uri's authority is used to
  determine the host, port, etc. for a filesystem.</description>
</property>

#10 Edite o arquivo mapred-site.xml entre as tags <configuration> coloque o conteudo abaixo.

gedit conf/mapred-site.xml

<property>
  <name>mapred.job.tracker</name>
  <value>localhost:54311</value>
  <description>The host and port that the MapReduce job tracker runs
  at.  If "local", then jobs are run in-process as a single map
  and reduce task.
  </description>
</property>

#11 Edite o arquivo hdfs-site.xml entre as tags <configuration> coloque o conteudo abaixo.

gedit conf/hdfs-site.xml

<property>
  <name>dfs.replication</name>
  <value>1</value>
  <description>Default block replication.
  The actual number of replications can be specified when the file is created.
  The default is used if replication is not specified in create time.
  </description>
</property>

########## Adaptação do ambiente Hadoop para compilação C++ (2 passos) ##########

#1 Instalação das libs (apt-get)

apt-get install g++
apt-get install libssl-dev
apt-get install glibc-devel
apt-get install ia32-libs 
find / -iname attempt_* 2>/dev/null
find / -iname stubs 2>/dev/null
apt-cache search glibc
apt-cache search libc6-dev
apt-get install libc6-dev-i386

#2 Utilizar ubuntu atualizado se possível.

########## Mudança para configuração distribuída do Hadoop (6 passos) ##########

#1 Em cada nó libere o SSH para todos os demais nós através dos comandos: (Mude user pelo nome do usuário e computer para cada computador da grid de máquinas)

ssh-keygen
ssh-copy-id -i $HOME/.ssh/id_rsa.pub user@computer

#2 Adicione no arquivo slaves da pasta Hadoop o nome de rede de todos os computadores que devem executar a aplicação

#3 Edite o arquivo core-site.xml. Substitua master pelo nome de rede do computador que irá disparar a aplicação.

gedit conf/core-site.xml

<property>
  <name>hadoop.tmp.dir</name>
  <value>/home/user/hadoop/tmp</value>
  <description>A base for other temporary directories.</description>
</property>

<property>
  <name>fs.default.name</name>
  <value>hdfs://master:54310</value>
  <description>The name of the default file system.  A URI whose
  scheme and authority determine the FileSystem implementation.  The
  uri's scheme determines the config property (fs.SCHEME.impl) naming
  the FileSystem implementation class.  The uri's authority is used to
  determine the host, port, etc. for a filesystem.</description>
</property>

#4 Rode o script start-all.sh em todas as máquinas que foram adicionadas no arquivo slaves.

#5 Execute jps em cada nó, apenas o mestre deverá estar rodando o NameSpace, sendo que cada nó slave deverá rodar o DataNode.

#6 Compile e execute os passos a seguir (Seja para C++ ou Java).

########## Compilação e execução do código Java (5 passos) ##########

#1 Habilite o Hadoop e monte o HDFS
start-all.sh
hadoop dfsadmin -safemode leave

#2 Carregue os dado da aplicação (BigPatientsData) / (generef) / (db) (Troque Raffael pelo usuário)

hadoop dfs -rmr /user/raffael/input
hadoop dfs -mkdir input
hadoop dfs -copyFromLocal /home/raffael/BigPatientsData.txt input
hadoop dfs -ls input

hadoop dfs -rmr /user/raffael/db
hadoop dfs -mkdir db
hadoop dfs -copyFromLocal /home/raffael/db/*.* db
hadoop dfs -ls db

hadoop dfs -rmr /user/raffael/generef
hadoop dfs -mkdir generef
hadoop dfs -copyFromLocal /home/raffael/generef/*.* generef
hadoop dfs -ls generef

#3 Compile o codigo C++

rm -Rf App_classes
mkdir App_classes
javac -cp `hadoop classpath` DiseaseApplication.java -d App_classes
rm -Rf diseaseapp.jar
jar -cvf diseaseapp.jar -C App_classes/ .

#4 Execute a aplicação

hadoop dfs -rmr output
hadoop jar diseaseapp.jar org.HCPAtools.Hadoop.DiseaseApplication input output


#5 Visualize a saída do código

hadoop dfs -cat /user/raffael/output/part-r-00000

########## Compilação e execução e visualização do código C++ (6 passos) ##########


#1 Habilite o Hadoop e monte o HDFS
start-all.sh
hadoop dfsadmin -safemode leave

#2 Carregue os dado da aplicação (BigPatientsData) (Troque Raffael pelo usuário)

hadoop dfs -rmr /user/raffael/input
hadoop dfs -mkdir input
hadoop dfs -copyFromLocal /home/raffael/BigPatientsData.txt input
hadoop dfs -ls input

#3 Compile o codigo C++

g++ -I/home/raffael/hadoop/src/c++/install/include  -L/home/raffael/hadoop/src/c++/install/lib DiseaseC++.cpp -lpthread -lhadooppipes -lhadooputils -lcrypto -o code

#4 Copie o código para o diretório bin no HDFS do Hadoop

hadoop dfs -rmr bin
hadoop dfs -mkdir bin
hadoop dfs -copyFromLocal code bin

#5 Execute a aplicação

hadoop dfs -rmr output
hadoop pipes -D hadoop.pipes.java.recordreader=true -D hadoop.pipes.java.recordwriter=true -input input -output output -program bin/code

#6 Visualize a saída do código

hadoop dfs -cat /user/raffael/output/part-r-00000
