import pdb
# pdb.set_trace()

s = "dvdf"
temp = set()
max_length = tlength = 0
for i in s:
    if i in temp:
        if max_length < tlength:
            max_length = tlength
        tlength = 0
        temp.clear()
        temp.add(i)
        tlength += 1
    else:
        temp.add(i)
        tlength += 1
        

print(max_length)