import pyperclip

merged_cc = ''
with open('a.cc', 'r') as f:
    for line in f:
        if line.startswith('#include'):
            s = line.split('"')
            with open(s[1], 'r') as f:
                header = f.read()
            merged_cc += header
        else:
            merged_cc += line
pyperclip.copy(merged_cc)
line_cnt = merged_cc.count('\n') + 1
print(f'{line_cnt} lines copied into clipboard.')
