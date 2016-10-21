#PYTHON 3
#BRANDON M ROACH
#FIXES WEAK FLAGS IN RAPP REACTION FILES

import string

input_path = 'rapp_rates_unedited/reac'
output_path = 'rapp_rates_fixed/reac'

for i in range(1,62506): #files are [reac1.dat, reac62505.dat]
    fin = open(input_path+str(i)+'.dat','r')
    fout = open(output_path+str(i)+'.dat','w')
    test = open('test.txt','w')

    lines=fin.readlines()

    for k, line in enumerate(lines):
        if k==1: #all changes are on the second line

            if r'bet-' in line:
                fout.write(line.replace(r'bet- ',r'bet-w'))
            
            elif r'bet+' in line:
                fout.write(line.replace(r'bet+ ',r'bet+w'))
                
            elif r'bkmo' in line:
                fout.write(line.replace(r'bkmo ',r'bkmow'))
                    
            elif r'btyk' in line:
                fout.write(line.replace(r'btyk ','btykw'))
                        
            elif r'bqa+' in line:
                fout.write(line.replace(r'bqa+ ','bqa+w'))
                            
            elif r' ec ' in line:
                fout.write(line.replace(r' ec ', r' ecw'))
                                
            elif r' bec ' in line:
                fout.write(line.replace(r' bec ', r' becw'))
                                    
            elif r'bhi+' in line:
                fout.write(line.replace(r'bhi+ ', r'bhi+w'))
            
            elif r'bex+' in line:
                fout.write(line.replace(r'bex+ ', r'bex+w'))
            
            elif r'     mo92     ' in line: #5 spaces before and behind
                fout.write(line.replace(r'mo92 ',r'mo92w'))
            
            elif r'mo03' in line:
                fout.write(line.repalce(r'mo03 ',r'mo03w'))


            else:
                fout.write(line) #if there was nothing to replace, re-write it
        
        else: #if we weren't on the second line, just re-write the original line
            fout.write(line)

    fin.close()
    fout.close()
    test.close()
    
    
