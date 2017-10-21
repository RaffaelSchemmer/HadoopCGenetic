import shutil
import sys
      
file_name = "/home/user/code/PatientsData.txt"
BI_file_name = "/home/user/code/BigPatientsData.txt"

destination = open(BI_file_name,'wb')

i = 1 
while(i < 101):
	shutil.copyfileobj(open(file_name,'rb'), destination)
	i += 1

destination.close()
