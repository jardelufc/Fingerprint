function rpl(caminho)
% reference point location para imagens de impressão 
% digital que sao passadas por parâmetro.
% autor: jilseph

close all; 

Alin = -1;
Acol = -1;
img = double(imread(caminho)); % carregando imagem
[lin, col] = size(img); 
wphi = 5;

% Aplicando o filtro de sobel
disp('Aplicando filtro de sobel');
tic;
GxMask = [1 0 -1; 2 0 -2; 1 0 -1]; 
GyMask = [1 2 1; 0 0 0; -1 -2 -1];
Gx = imfilter(img, GxMask, 'same'); 
Gy = imfilter(img, GyMask, 'same'); 
G = sqrt( Gx.^2 + Gy.^2 ); 
tetaG = atan( Gy ./ Gx ); 
disp(['duracao: ' num2str(toc)]);


for w = 25:-1:1

    disp('---'); 
    disp(['Analisando para W = ' num2str(w)]); 
    disp('   ');

    % Estimando a orientacao local de cada bloco w x w
    disp('Estimando a orientacao local de cada bloco w x w'); 
    tic;
    Vx = zeros(lin, col);
    Vy = zeros(lin, col);
    O = zeros(lin, col);
    for i = 1:lin
        for j = 1:col
            wp2 = floor(w/2); % wp2 = w por 2
            
            umin = i-wp2;
            umax = i+wp2;
            vmin = j-wp2;
            vmax = j+wp2;
            
            if umin < 1
                umin = 1;
            end
            if umax > lin
                umax = lin;
            end
            if vmin < 1
                vmin = 1;
            end
            if vmax > col
                vmax = col;
            end
            
            u = umin:umax;
            v = vmin:vmax;
            
            GX = Gx(u,v);
            GY = Gy(u,v); 
            
            sumX = sum(sum( 2 .* GX .* GY ));
            sumY = sum(sum( (GX.^2 - GY.^2) )); 
            
            Vx(i,j) = sumX;
            Vy(i,j) = sumY; 
            O(i,j) = 0.5 * atan( sumY/sumX ); 
        end
    end
    disp(['duracao: ' num2str(toc)]);

    % Smooth the orientation field in a local neighborhood.
    disp('Smooth the orientation field in a local neighborhood'); 
    tic;
    phiX = cos( 2.*O ); 
    phiY = sin( 2.*O );
    W = ones(wphi)./(wphi^2);
    phiXlinha = imfilter(phiX, W, 'same'); 
    phiYlinha = imfilter(phiY, W, 'same'); 
    Olinha = 0.5 .* atan( phiYlinha./phiXlinha );
    disp(['duracao: ' num2str(toc)]);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    % Calculando E
    disp('Calculando E');
    tic;
    E = sin(Olinha); 
    disp(['duracao: ' num2str(toc)]);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    %%%%%%%% Determinando A
    disp('Determinando A');
    tic;
    % calculando mascara da regiao I e regiao II
    regionI = zeros(2*w+1); 
    regionII = zeros(2*w+1);  
    [M,N] = size(regionI); 
    xc = floor(M/2)+1;
    yc = xc;
    for i = 1:M
        y = (-1) * (i - yc);
        for j = 1:N
            x = j - xc; 
            if i <= yc % testando apenas para o semicirculo superior
                r = sqrt(x^2 + y^2); 
                if r <= w
                    % atand so gera resultado de -90° a 90°
                    % fazendo com que atand gere resultado de 0 a 90°
                    % por quadrante comecado do eixo x para o eixo y
                    % isto funciona apenas para o semicirculo superior
                    teta = abs(atand(y/x)); 
                    if teta <= 45
                        regionI(i,j) = 1;
                    else
                        regionII(i,j) = 1; 
                    end
                end
            end
        end
    end
    % calculando A
    AregionI = imfilter(E, regionI, 'same'); 
    AregionII = imfilter(E, regionII, 'same'); 
    A = AregionI - AregionII; 
    disp(['duracao: ' num2str(toc)]);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % Retornando o maior valor de A
    disp('Retornando o maior valor de A'); 
    tic;
    if 1
        [Alin, Acol] = find(A == max(max(A)));
    else
        % Extraindo submatriz de A
        minAlin = Alin-35; 
        if minAlin < 1
            minAlin = 1;
        end            
        maxAlin = Alin+35;
        if maxAlin > lin
            maxAlin = lin;
        end
        minAcol = Acol-35;
        if minAcol < 1
            minAcol = 1;
        end
        maxAcol = Acol+35;
        if maxAcol > col
            maxAcol = col;
        end
        subA = A( minAlin:maxAlin, minAcol:maxAcol );
        [Alin, Acol] = find(subA == max(max(subA))); 
        Alin = Alin + minAlin - 1;
        Acol = Acol + minAcol - 1;
    end
    disp(['Valor na posicao (' num2str(Alin) ',' num2str(Acol) ')']); 
    disp(['duracao: ' num2str(toc)]);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % Pintando o ponto encontrado
    imgFinal = img; 
    for i = Alin-11:Alin+11
        for j = Acol-11:Acol+11
            if i > 0 && j > 0 && i <= lin && j <= col
                imgFinal(i,j) = 255; 
            end
        end
    end
    
    % Rescalando phiXlinha e phiYlinha para mostrar na tela
    phiXlinha = rescale(phiXlinha); 
    phiYlinha = rescale(phiYlinha); 
    E = rescale(E);
    A = rescale(A); 

    % mostrando figuras
%     figure('name', ['Para W = ' num2str(w)]);
%     subplot(2,6,1), imshow(uint8(img)), title('original'); 
%     subplot(2,6,2), imshow(Vx), title('Vx'); 
%     subplot(2,6,3), imshow(Vy), title('Vy'); 
%     subplot(2,6,4), imshow(O), title('O'); 
%     subplot(2,6,5), imshow(phiXlinha), title('phiX''');
%     subplot(2,6,6), imshow(phiYlinha), title('phiY''');
%     subplot(2,6,7), imshow(Olinha), title('O''');
%     subplot(2,6,8), imshow(E), title('E');
%     subplot(2,6,9), imshow(regionI), title('Região I');
%     subplot(2,6,10), imshow(regionII), title('Região II');
%     subplot(2,6,11), imshow(A), title('A');
%     subplot(2,6,12), imshow(uint8(imgFinal)), title('final');
    
    % Salvando imagem
    disp('Salvando imagem...'); 
    imwrite(uint8(imgFinal), ['w=' num2str(w) '.jpg'], 'jpg'); 
    
    disp('---');
    disp('   ');
end

function res = rescale(img)
% rescala imagem para nivel de cinza

minx = min(min(img));
if minx < 0
    res = img + abs(minx); 
else
    res = img; 
end
res = uint8(255.*(res./max(max(res)))); 