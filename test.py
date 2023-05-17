"""import subprocess
import time
print("graph time: ")
start_time = time.time()
str = subprocess.run(['main.exe', '5', '10'], stdout=subprocess.PIPE).stdout.decode('utf-8').rstrip()
print(time.time() - start_time)
print("graph_v2 time:")
start_time = time.time()
str = subprocess.run(['test.exe', '5', '10'], stdout=subprocess.PIPE).stdout.decode('utf-8').rstrip()
print(time.time() - start_time)"""

def read_single_digits(file):
    lines = file.readlines()
    count = 0
    result = '{'
    for l in lines:
        result += l.strip() + ','
        if(not(count % 50)):
            result += '\n'
        count += 1
    result += '}'
    return result

def read_connections(file):
    lines = file.readlines()
    count = 1
    aux_string = ''
    res = open("processed_connections.txt", "a")
    for l in lines:
        aux_string += '{' + l.strip() + '},'
        res.write(aux_string)
        if((count % 3)==0):
            res.write('\n')
        aux_string = ''
        count += 1
    res.close()
        

#print(read_single_digits(open('arcs.csv')))
read_connections(open('connections.csv'))