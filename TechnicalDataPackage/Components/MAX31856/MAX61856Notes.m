%Analysis related to the MAX31856
%
%Christopher Lum
%lum@uw.edu

%Version History
%11/30/24: Created

clear
clc
close all

tic

Table2_binary = [
0	0	0	1	0	1	1	0	1	1	1	1	0	1	0	0
0	0	0	1	0	1	1	0	1	1	1	1	0	0	1	1
0	0	0	1	0	1	1	0	1	1	1	1	0	0	1	0
0	0	0	1	0	1	1	0	1	1	1	1	0	0	0	1
0	0	0	1	0	1	1	0	1	1	1	1	0	0	0	0
0	0	0	1	0	1	1	0	1	1	1	0	1	1	1	1
0	0	0	1	0	1	1	0	1	1	1	0	1	1	1	0
0	0	0	1	0	1	1	0	1	1	1	0	1	1	0	1
0	0	0	1	0	1	1	0	1	1	1	0	1	1	0	0
    ];

%Convert to a char array
[M,N] = size(Table2_binary);

binaryChar = {};
for k=1:M
    rowBinary = Table2_binary(k,:);
    rowChar = strrep(num2str(rowBinary),' ','');
    binaryChar{k,1} = rowChar;
end

%Convert each row to int16 and temperature
for k=1:M
    Table2_int16(k,1)   = BinaryToInt16(binaryChar{k});
    temperature_C(k,1)  = double(Table2_int16(k,1))/256.0;
end

%Analyze the MSB and LSB
MSB = {};
LSB = {};
MSB_uint8 = [];
LSB_uint8 = [];
for k=1:M
    rowBinary = binaryChar{k};
    MSB_k = rowBinary(1:8);
    LSB_k = rowBinary(9:16);
    MSB{k,1} = MSB_k;
    LSB{k,1} = LSB_k;

    MSB_uint8(k,1) = BinaryToUint8(MSB_k);
    LSB_uint8(k,1) = BinaryToUint8(LSB_k);
    
    % rowChar = strrep(num2str(rowBinary),' ','');
    % MSB_uint16(k,1) = BinaryToUint8(rowChar);
end


%Create a table
T = table(binaryChar,Table2_int16,temperature_C,MSB,LSB,MSB_uint8,LSB_uint8)


return

%The minimum is clamped at -64 degrees.  
%
%   binary  1100 0000 0000 0000
%   decimal -16384
k = 1;
for val = -1:-1:-25
    i16 = int16(val);
    c = Int16ToBinary(i16);

    data{k,1} = i16;
    data{k,2} = c;
    
    k = k + 1;
end

data

toc
disp('DONE!')