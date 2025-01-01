clc; clear; close all;

%Time spent
% Read data files for FPGA, ARM Processor, and Laptop CPU
data = readtable('fpga.csv');
X = rmoutliers(data.Var1);
% figure
% hist(X, 40)
% mean(X)
% std(X)
% figure
% qqplot(X)
timeMedianFPGA = median(X)/1000;
% MEDIAN 95 mikrosekunder

dataCpu = readtable('u_96_cpu.csv');
XCpu = rmoutliers(dataCpu.Var1);
% figure
% hist(XCpu, 40)
% mean(XCpu)
% std(XCpu)
% figure
% qqplot(XCpu)
timeMedianCpu = median(XCpu)/1000;
% MEDIAN 146 mikrosekunder

dataLapCpu = readtable('laptop_cpu.csv');
XLapCpu = rmoutliers(dataLapCpu.Var1);
% figure
% hist(XLapCpu, 40)
% mean(XLapCpu)
% std(XLapCpu)
% figure
% qqplot(XLapCpu)
timeMedianLapCpu = median(XLapCpu)/1000;
% MEDIAN 29 mikrosekunder

% Data Preparation for Comparison
platforms = {'FPGA', 'ARM Processor', 'Laptop CPU'};

% Median times
timeMedians = [timeMedianFPGA, timeMedianCpu, timeMedianLapCpu];

% Power consumption (Watts)
fpgaPower = 0.481;
cpuPower = 1.853;
lapCpuPower = 45;
power = [fpgaPower, cpuPower, lapCpuPower];

% Power efficiency
efficiency = [timeMedianFPGA*fpgaPower, timeMedianCpu*cpuPower, timeMedianLapCpu*lapCpuPower];

% Create the figure
figure;

% Plot 1: Median Time
subplot(1, 3, 1);  % 1 row, 3 columns, this is the first subplot
hBar1 = bar(timeMedians);
hBar1.FaceColor = 'flat';
hBar1.CData = [0, 0.4470, 0.7410;   % Red for FPGA
              0.8500, 0.3250, 0.0980;   % Green for ARM Processor
              0.9290, 0.6940, 0.1250];  % Blue for Laptop CPU
set(gca, 'XTickLabel', platforms, 'FontSize', 12);
ylabel({'Median Time (μs)', 'Lower is better'}, 'FontSize', 12);
title('Median Time Comparison', 'FontSize', 14);
for i = 1:length(timeMedians)
    text(i, timeMedians(i), sprintf('%.2f', timeMedians(i)), 'HorizontalAlignment', 'center', 'VerticalAlignment', 'bottom');
end
grid on;

% Plot 2: Power
subplot(1, 3, 2);  % 1 row, 3 columns, this is the second subplot
hBar2 = bar(power);
hBar2.FaceColor = 'flat';
hBar2.CData = [0, 0.4470, 0.7410;   % Red for FPGA
              0.8500, 0.3250, 0.0980;   % Green for ARM Processor
              0.9290, 0.6940, 0.1250];  % Blue for Laptop CPU
set(gca, 'XTickLabel', platforms, 'FontSize', 12);
ylim([0 46])
ylabel({'Power (W)', 'Lower is better'}, 'FontSize', 12);
title('Power Comparison', 'FontSize', 14);
for i = 1:length(power)
    text(i, power(i), sprintf('%.2f', power(i)), 'HorizontalAlignment', 'center', 'VerticalAlignment', 'bottom');
end
grid on;

% Plot 3: Median Efficiency
subplot(1, 3, 3);  % 1 row, 3 columns, this is the third subplot
hBar3 = bar(efficiency);
hBar3.FaceColor = 'flat';
hBar3.CData = [0, 0.4470, 0.7410;   % Red for FPGA
              0.8500, 0.3250, 0.0980;   % Green for ARM Processor
              0.9290, 0.6940, 0.1250];  % Blue for Laptop CPU
set(gca, 'XTickLabel', platforms, 'FontSize', 12);
ylabel({'Efficiency (W x μs = μJ)', 'Lower is better'}, 'FontSize', 12);
ylim([0 1360])
title('Efficiency Comparison', 'FontSize', 14);
for i = 1:length(efficiency)
    text(i, efficiency(i), sprintf('%.2f', efficiency(i)), 'HorizontalAlignment', 'center', 'VerticalAlignment', 'bottom');
end
grid on;
