Hadoop C for DNA Sequencing
===========================

Instale o Haodop seguindo os tutoriais do white book.
Adaptação do ambiente Hadoop para compilação C++ (2 passos)

[1] Instalação das libs (apt-get)

apt-get install g++
apt-get install libssl-dev
apt-get install glibc-devel
apt-get install ia32-libs 
find / -iname attempt_* 2>/dev/null
find / -iname stubs 2>/dev/null
apt-cache search glibc
apt-cache search libc6-dev
apt-get install libc6-dev-i386

[2] Utilizar ubuntu atualizado se possível.

Mudança para configuração distribuída do Hadoop (6 passos)

[1] Em cada nó libere o SSH para todos os demais nós através dos comandos: 

(Mude user pelo nome do usuário e computer para cada computador da grid de máquinas)

ssh-keygen
ssh-copy-id -i $HOME/.ssh/id_rsa.pub user@computer

[2] Adicione no arquivo slaves da pasta Hadoop o nome de rede de todos os computadores que devem executar a aplicação

[3] Edite o arquivo core-site.xml. Substitua master pelo nome de rede do computador que irá disparar a aplicação.

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

[4] Rode o script start-all.sh em todas as máquinas que foram adicionadas no arquivo slaves.

[5] Execute jps em cada nó, apenas o mestre deverá estar rodando o NameSpace, sendo que cada nó slave deverá rodar o DataNode.

[6] Compile e execute os passos a seguir (Seja para C++ ou Java).

Compilação e execução do código Java (5 passos)

[1] Habilite o Hadoop e monte o HDFS
start-all.sh
hadoop dfsadmin -safemode leave

[2] Carregue os dado da aplicação (BigPatientsData) / (generef) / (db) (Troque Raffael pelo usuário)

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

[3] Compile o codigo C++

rm -Rf App_classes
mkdir App_classes
javac -cp `hadoop classpath` DiseaseApplication.java -d App_classes
rm -Rf diseaseapp.jar
jar -cvf diseaseapp.jar -C App_classes/ .

[4] Execute a aplicação

hadoop dfs -rmr output
hadoop jar diseaseapp.jar org.HCPAtools.Hadoop.DiseaseApplication input output

[5] Visualize a saída do código

hadoop dfs -cat /user/raffael/output/part-r-00000

Compilação e execução e visualização do código C++ (6 passos)

[1] Habilite o Hadoop e monte o HDFS
start-all.sh
hadoop dfsadmin -safemode leave

[2] Carregue os dado da aplicação (BigPatientsData) (Troque Raffael pelo usuário)

hadoop dfs -rmr /user/raffael/input
hadoop dfs -mkdir input
hadoop dfs -copyFromLocal /home/raffael/BigPatientsData.txt input
hadoop dfs -ls input

[3] Compile o codigo C++

g++ -I/home/raffael/hadoop/src/c++/install/include  -L/home/raffael/hadoop/src/c++/install/lib DiseaseC++.cpp -lpthread -lhadooppipes -lhadooputils -lcrypto -o code

[4] Copie o código para o diretório bin no HDFS do Hadoop

hadoop dfs -rmr bin
hadoop dfs -mkdir bin
hadoop dfs -copyFromLocal code bin

[5] Execute a aplicação

hadoop dfs -rmr output
hadoop pipes -D hadoop.pipes.java.recordreader=true -D hadoop.pipes.java.recordwriter=true -input input -output output -program bin/code

[6] Visualize a saída do código

hadoop dfs -cat /user/raffael/output/part-r-00000
