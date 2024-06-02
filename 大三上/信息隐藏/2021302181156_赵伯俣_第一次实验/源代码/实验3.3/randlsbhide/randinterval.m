function [row,col]=randinterval(matrix,count,key)
%计算间隔的位数
[m,n]=size(matrix);
interval1=floor(m*n/count)+1;
interval2= interval1-2;
if interval2==0
   error('载体大小不能将秘密信息隐藏进去!');
end
%生成随机序列
rand('seed',key);
a=rand(1,count);
%计算row和col
r=1;
c=1;
row(1,1)=r;
col(1,1)=c;
for i=2:count
    if a(i)>=0.5
    c=c+interval1;
    else
        c=c+ interval2;
    end
    if c>n
        r=r+1;
    if r>m
        error('载体大小不能将秘密信息隐藏进去!');
    end
    c=mod(c,n);
    if c==0
        c=1;
    end
    end
row(1,i)=r;
col(1,i)=c;
end