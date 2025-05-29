clear all;close all;clc;

img = imread("p_grafico/1k.jpg");
%img = imread("P3.jpg");
 

%img = imread("IMG_20243526_0335559222751862295569120.jpg");

%img = imread("anexos/20240109_204349.jpg");
% img = imread("anexos/20240109_204357.jpg");
%img = imread("20240107_204717.jpg");
% img = imread("01.jpg");
%img = imread("../SourceFiles/test.jpg");
% img = imread("03.jpg");
% img = imread("04.jpg");

%img = imread("1over6k.jpg");
%img = imread("1over2k.jpg");

%10khz sampling de um sinal 4khz
%img = imread("IMG_20244605_0746095672632437283726949.jpg");
%img = imread("IMG_20244605_0746196581808631262600906.jpg");

sizeImg = size(img);

filterOrder = floor(min(sizeImg(1:2))/30);
filterOrder =59;
%filterOrder = 100;
%filterOrder = 7;
tic;
img = findCenterOfBlobs(img, filterOrder, true);
toc;
% img01gray = rgb2gray(img01);
% img02gray = rgb2gray(img02);
% img03gray = rgb2gray(img03);
% img04gray = rgb2gray(img04);
% 
% a = 100;
% filter = (1/(a^2)) * ones(a,a);
% img01blurr = imfilter(img01gray, filter);
% 
% hist01 = imhist(img01blurr);
% hist02 = imhist(img02gray);
% hist03 = imhist(img03gray);
% hist04 = imhist(img04gray);
% 
% otsuthresh01 = otsuthresh(hist01);
% otsuthresh02 = otsuthresh(hist02);
% otsuthresh03 = otsuthresh(hist03);
% otsuthresh04 = otsuthresh(hist04);
% 
% img01bw = imbinarize(img01blurr,otsuthresh01);
% 
% figure, imshow(img01);
% figure, imshow(img01gray);
% figure, imshow(img01blurr);
% figure, imshow(img01bw);
% figure, plot(hist01);

%%so para criar dilatacao usada no tcc texto
%{ 
%%
img = imread("IMG_20244605_0746095672632437283726949.jpg");
img = im2gray(img);
se = strel("line",20,90);
img = imbinarize(img);
i = imdilate(img,se);
imshow(i);
se = strel("line",30,90);
ii = imdilate(img,se);
imshow(ii);
imwrite(ii,"img_intro_dilated.jpg")
se = strel("line",31,90);
ii = imdilate(img,se);
imwrite(ii,"img_intro_dilated.jpg")


%}
%imtool("IMG_20252417_0524394613070876109431805.jpg");
%imtool("../../p4p_c_test/pics_v2/02/IMG_20254217_0742051636124383349867322.jpg");
%%

%%heatmap

img = imread("IMG_20243526_0335559222751862295569120.jpg");
img2 = img2gray(img);
 
img2 = im2gray(img);
img2 = im2double(img2);
h2 = imagesc(img2);
h2 = imagesc(img2);
