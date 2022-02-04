% s = serial('COM7','BaudRate',9600,'DataBits',8);
% out = instrfind;
% fclose(s);
% fopen(s);
% voltage=fscanf(s)
% fclose(s);
% 
% function [s,flag]=setupSerial(comPort)
% flag=1;
% s=serial(comPort);
% set(s,"DataBits",8);
% set(s,"StopBits",1);
% set(s,"BaudRate",9600);
% set(s,"parity","none");
% fopen(s);
% a="b";
% while (a~="a")
%     a=fread(s,1,"uchar");
% end
% if(a=="a")
%     disp("serial read");
% end
%     fprintf(s,"%c","a");
%     mbox=msgbox("serial communication setup.");uiwait(mbox);
%     fscanf(s,"%u");
% end
%      

 clear
 clc
s=serial('COM7','BaudRate',9600);
fopen(s);
 readData=fscanf(s) %reads "Ready" 
writedata=uint16(6500); %0x01F4
fwrite(s,writedata,'uint16') %write data
 for i=1:2 %read 2 lines of data
readData=fscanf(s)
end
 fclose(s);
 delete(s);
























