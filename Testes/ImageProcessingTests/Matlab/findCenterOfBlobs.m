function [returnImage] = findCenterOfBlobs(image, filterOrder, plotImages)
%FINDCENTEROFBLOBS Summary of this function goes here
%   Detailed explanation goes here

if(plotImages)
    figure, imshow(image);
end

filter = ones(filterOrder, filterOrder) * (1/(filterOrder^2));

returnImage = im2gray(image);

if(plotImages)
    figure, imshow(returnImage);
end

returnImage = imfilter(returnImage, filter);

if(plotImages)
    figure, imshow(returnImage);
end

%hist = imhist(returnImage);
%
%otsuThreshold = otsuthresh(hist);

%já usa otsu
returnImage = imbinarize(returnImage);

if(plotImages)
    figure, imshow(returnImage);
end

blobOutline = bwboundaries(returnImage);
%visboundaries(returnImage);
minXBlob = min(blobOutline{1}(:,2));
minYBlob = min(blobOutline{1}(:,1));

maxXBlob = max(blobOutline{1}(:,2));
maxYBlob = max(blobOutline{1}(:,1));

rectanglePosition = [minXBlob, minYBlob, maxXBlob - minXBlob, maxYBlob - minYBlob];

if(plotImages)
    figure, imshow(image);
    hold on;
    rectangle('Position', rectanglePosition, 'EdgeColor','r');
    hold off;
end

aux = im2gray(image);
aux = imbinarize(aux);
aux = im2double(aux);
blobMean = zeros([1,maxYBlob - minYBlob + 1]);
index = 1;
for hIndex = minYBlob:1:maxYBlob
    for wIndex = minXBlob:1:maxXBlob
        blobMean(index) = blobMean(index) + aux(hIndex, wIndex);
    end
    % if blobMean(index) > (maxYBlob - minYBlob)/2
    %     blobMean(index) = 1;
    % else
    %     blobMean(index) = 0;
    % end
    index = index + 1;
end

figure, plot(blobMean);
hold on;
blobThreshold = mean(blobMean);
for index = 1:1:maxYBlob - minYBlob + 1
    if blobMean(index) >= blobThreshold
        blobMean(index) = blobThreshold;
    else
        blobMean(index) = 0;
    end
end
%blobMean = blobMean.*aux;
plot(blobMean);
hold off;
%encontra os blobs
% [width, height] = size(returnImage);
% auxImage = returnImage;
% BlobCoordinates = -1;
% for wIndex = 1:1:width
%     for hIndex = 1:1:height
%         if auxImage(wIndex, hIndex) == 1
%             [aux, auxImage] = ...
%                     getCoordinatesOfBlob([wIndex, hIndex], auxImage);
%             if isa(BlobCoordinates,'cell')
%                 BlobCoordinates = [BlobCoordinates; aux];
%             else
%                 BlobCoordinates = aux;
%             end
%         end
%     end
% end
% 
% pause            
    
end

