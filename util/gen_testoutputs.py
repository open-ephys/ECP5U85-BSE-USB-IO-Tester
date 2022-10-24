"""
Very simple and hacky script to create a list of assignments from the analog multiplexer inputs
Netlist needs to be exported in OrCADPCB2 format and the reailing asterisk manually removed 

Probably should make filenames and part number a proper argument, but I am lazy right now
"""
import sexpdata
import re

filename = "netlist.net" #input file
outputfile = "assign.v" #output file
maxparts = 8
partname = "74HCT4067PW"
portlist = [9, 8, 7, 6, 5, 4, 3, 2, 23, 22, 21, 20, 19, 18, 17, 16]
portoffset = 3
shiftname = "shiftreg"

def sanitize(port):
    
    #general cleans
    net = re.findall('/*(?:.+/)*(.+)',port.tosexp())[0]
    
    if val := re.match('\~\{(.+)\}',net):
        net = val[1] + 'n'
    elif val := re.match('(.+)\+',net):
        net = val[1] + '_p'
    elif val := re.match('(.+)\-',net):
        net = val[1] + '_n'
    
    #port-specific
    if val := re.match('(D\dIO?)(\d+)(.*)',net):
        net = '{pre}{sub}[{idx}]'.format(pre = val[1],sub = val[3],idx = val[2])
    elif val := re.match('(S\d)(\d+)',net):
        net = '{pre}[{idx}]'.format(pre = val[1], idx = val[2])
    elif val := re.match('(\D+)(\d+)',net):
        net = '{pre}[{idx}]'.format(pre = val[1], idx = val[2])
        
    return(net)
    

def main():
    file = open(filename,"r")
    data = file.read()
    file.close()
    sdata = sexpdata.loads(data)
    
    numports = len(portlist)
    muxes = [[""]*numports for i in range(maxparts)]
    
    for part in sdata:
        if not(type(part) is list):
            continue
        
        if not(re.match("U\d+",part[2].tosexp())):
            continue
        if re.match(partname+".*",part[3].tosexp()):
            if val := re.match("/Test_\{(\d+)\}",part[1+portoffset][1].tosexp()):
                mux = int(val[1])
                for i in range(len(portlist)):
                    muxes[mux][i]=sanitize(part[portlist[i]+portoffset][1])

                    
    file = open(outputfile,"w")
    
    shiftindex = 0
    muxnumber = 0
    for m in muxes:
        file.write("//Test " + str(muxnumber) + "\n")
        muxnumber = muxnumber + 1
        portnumber = 0
        for p in m:
            if (p == "GND"):
                file.write("//")
            file.write("assign "+p+"    = " + shiftname +"["+str(shiftindex)+"]; //"+str(portnumber)+"\n")
            portnumber = portnumber+1
            shiftindex = shiftindex +1
        file.write("\n")
            
    file.close()
    
if __name__ == "__main__":
    main()