clear all;close all;clc;
%img = imread("p_grafico/1k.jpg");
%img = imread("p_grafico/1_5k.jpg");
%img = imread("p_grafico/2k.jpg");
%img = imread("p_grafico/2_5k.jpg");
%img = imread("p_grafico/dca.jpg");
%img = imread("p_grafico/dcb.jpg");

%img = imread("p_grafico/fig55/1k.jpg");
%img = imread("p_grafico/fig55/1_5k.jpg");
%img = imread("p_grafico/fig55/2k.jpg");
%img = imread("p_grafico/fig55/2_5k.jpg");
%img = imread("p_grafico/fig55/dca.jpg");
img = imread("p_grafico/fig55/dcb.jpg");

s = size(img);

minXBlob = 1;
minYBlob = 1;

maxXBlob = s(2);
maxYBlob = s(1);

aux = im2gray(img);
aux = 255 * im2double(aux);

blobMean = zeros([1,maxYBlob - minYBlob + 1]);

index = 1;
for hIndex = minYBlob:1:maxYBlob
    for wIndex = minXBlob:1:maxXBlob
        blobMean(index) = blobMean(index) + aux(hIndex, wIndex);
    end
    index = index + 1;
end

figure, plot(blobMean);

hold on;

aux = im2gray(img);
aux = imbinarize(aux);
aux = 255 * im2double(aux);

index = 1;
for hIndex = minYBlob:1:maxYBlob
    blobMean(index) = 0;
    for wIndex = minXBlob:1:maxXBlob
        blobMean(index) = blobMean(index) + aux(hIndex, wIndex);
    end
    if(blobMean(index) > 255)
        %blobMean(index) = 255;
    end
    index = index + 1;
end

plot(blobMean);
xlabel("Linha");
ylabel("Valor da Escala em Cinza");
legend("Cinza", "Binarizada");