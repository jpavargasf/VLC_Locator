


function [BlobCoordinates,image] = getCoordinatesOfBlob(pixelCoordinates,image)
    
    x = pixelCoordinates(1);
    y = pixelCoordinates(2);

    

    [xSize, ySize] = size(image);

    if image(x,y) == 1 && ...
            x >= 1 && x <= xSize && ...
            y >= 1 && y <= ySize
        disp(image(x,y));
        image(x,y) = 0;
        
        BlobCoordinates = {[x,y]};
        
        %chama a função para os oito vizinhos
        
        for xPlus = -1:1:1
            for yPlus = -1:1:1
                
                [aux,image] = getCoordinatesOfBlob([x + xPlus, y + yPlus], image);
                if isa(aux,'cell')
                    BlobCoordinates = [BlobCoordinates, aux];
                end
            end
        end

    else
        %retorna nulo
        BlobCoordinates = -1;
    end
    
end

