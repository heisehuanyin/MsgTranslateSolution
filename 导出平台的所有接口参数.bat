echo 导出的界面中，输出格式范例中为整数的都是可以用来做判据的，默认十六进制，具体请咨询作者 > argslist.txt
cd Debug
MsgTranslateSolution.exe /expose >> ..\argslist.txt
cd ..
notepad argslist.txt