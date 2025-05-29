x = 0:2/1000:2;
y = -3.707066*x.^4 + 14.768799*x.^3 -22.148103*x.^2 + 14.820216*x.^1 -3.733552;
plot(x,y);

xlabel("x");
ylabel("y");
yline(0, '--k');
pause

y2 = -3.946276*x.^4 + 15.777310*x.^3 + -23.639893*x.^2 + 15.732834*x.^1  -3.923971;
figure, plot(x,y2);
xlabel("x");
ylabel("y");
yline(0, '--k');
x3 = 0.93:0.001:1.07;
y3 = -3.946276*x3.^4 + 15.777310*x3.^3 + -23.639893*x3.^2 + 15.732834*x3.^1  -3.923971;
figure, plot(x3,y3);
xlabel("x");
ylabel("y");
yline(0, '--k');
pause
close all;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ERRO%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%dlt
pontos = [3,1,2,4,5];
dlt_erro_medio = [0.213412099, 0.189070163, 0.292775172, 0.258537244, 0.149480657];
dlt_dp = [0.109554073,0.081425376,0.11669243,0.172191367,0.059593764];

errorbar(pontos,dlt_erro_medio, dlt_dp,'o' );
xlim([0.5,5.5]);
ylim([0,0.5]);
xticks([1,2,3,4,5]);
xlabel("Ponto");
ylabel("Erro (m)");
grid on;
%p4p
p4p_erro_medio = [0.480038773,1.134097025,0.862692654,0.981883478,0.451275328];
p4p_dp = [0.032326002,0.020944531,0.015723575,0.025827183,0.029067726];
figure, errorbar(pontos,p4p_erro_medio, p4p_dp,'o' );
xlim([0.5,5.5]);
%ylim([0,1.2]);
xticks([1,2,3,4,5]);
xlabel("Ponto");
ylabel("Erro (m)");
grid on;
hold on;

%p4pSimuladoSemErro_erro_medio = [0.194299349,0.162713852,0.166311374,0.192409578,0.18102175];
%p4pSimuladoSemErro_dp = [0.14397119,0.098497478,0.124056071,0.159507658,0.122104085];
%errorbar(pontos,p4pSimuladoSemErro_erro_medio, p4pSimuladoSemErro_dp,'o' );

p4pSimErro_erro_medio = [0.196156231,0.118540311,0.173959824,0.186239227,0.140079124];
p4pSimErro_dp = [0.142203785,0.07423438,0.112473616,0.124448534,0.094875175];
errorbar(pontos,p4pSimErro_erro_medio, p4pSimErro_dp,'o' );

%legend("P4P medido", "P4P sim.", "P4P sim. com erro");
legend("P4P medido", "P4P simulado");

%%%%%%%%%%%%%%%%%%ANGULAR
pontos_a = [1,2,3,4,5];
p6p_ax = [10.50264164,17.73704597,25.82849425,12.3135825,4.793446608];
p6p_ax_dp = [4.006701597,8.206162757,5.651955545,12.50692759,3.467656604];

p6p_ay = [6.315208875,6.816230003,11.38039288,3.869006461,3.965767933];
p6p_ay_dp = [2.973317116,3.321719475,3.199692812,3.591424582,2.697250863];

p6p_az = [10.17641217,17.28291734,24.63526172,12.56754561,4.220160075];
p6p_az_dp = [4.091217001,7.895949294,5.018148047,12.29872944,3.473308306];

figure, errorbar(pontos_a,p6p_ax, p6p_ax_dp,'o' );
hold on;
errorbar(pontos_a,p6p_ay, p6p_ay_dp,'x' );
errorbar(pontos_a,p6p_az, p6p_az_dp,'v' );
grid on;

xlim([0.5,5.5]);
xticks([1,2,3,4,5]);
ylim([0,35]);
legend("x", "y","z");
xlabel("Ponto de amostra");
ylabel("Erro(°)");

%%p4p
hold off;
p4p_ax = [0.321465548,1.08426842,7.316565251,2.315233744,6.547113876];
p4p_ax_dp = [0.222205256,0.646991446,8.523806199,1.563748552,4.189758314];

p4p_ay = [3.243471119,4.163253866,21.14398444,3.002127208,5.591182501];
p4p_ay_dp = [0.704096313,1.428010461,29.60081792,2.059279587,4.597395867];

p4p_az = [29.42131805,52.27868557,3.535455987,2.764312124,8.676191388];
p4p_az_dp = [0.104547835,0.114105075,1.09739978,1.686055665,4.654648164];

figure, errorbar(pontos_a,p4p_ax, p4p_ax_dp,'o' );
hold on;
errorbar(pontos_a,p4p_ay, p4p_ay_dp,'x' );
errorbar(pontos_a,p4p_az, p4p_az_dp,'v' );
grid on;

xlim([0.5,5.5]);
xticks([1,2,3,4,5]);
ylim([0,55]);
legend("x", "y","z");
xlabel("Ponto de amostra");
ylabel("Erro(°)");

