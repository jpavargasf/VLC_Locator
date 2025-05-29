%Autor: João Paulo Vargas da Fonseca
%Data: 29/04/2022
%Trabalho desenvolvido para a disciplina de Comunicações Digitais do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:
%
%Fs é a o número de amostras por segundo
%
%plot_options é um vetor de células de valores lógicos e de string
%1:boolean representa a opção de plotar em escala db
% 2:boolean opção de criar figura nova
% 3:boolean opção de hold on
% 4:boolean opção de mostrar legenda
% 5:string legenda do plot
function plot_frequency_domain(signal,Fs,title_txt,plot_options)
    n = length(signal);
    f = -Fs/2:Fs/n:Fs/2-Fs/n;
    x = abs(fftshift(fft(signal)))/n;
    
    if plot_options{1}
        x = 10*log(x);
        y_scale_txt = " (dB)";
    else
        y_scale_txt = "";
    end
    if plot_options{2}
        figure;
    end
    
    plot(f,x,'DisplayName',plot_options{5}),title(title_txt);
    ylabel("Amplitude"+y_scale_txt),xlabel("Frequência (Hz)");
    
    if plot_options{4}
        legend;
    end
    
    if plot_options{3}
        hold on;
    else
        hold off;
    end
end