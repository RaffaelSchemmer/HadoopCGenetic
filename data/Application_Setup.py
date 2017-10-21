import sys
import os
import shutil
import subprocess
	
print('gerando BigData (arquivo de entrada)...')
external_py_code = str('/home/user/code/text2BigInput.py')
subprocess.call([sys.executable, external_py_code])
src_file = '/home/user/code/PatientsData.txt'
dst_dir = '/home/user/code'
dst_file = str(dst_dir + '/PatientsData.txt')
