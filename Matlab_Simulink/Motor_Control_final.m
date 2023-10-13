clear all

%Load torque data 
torque_Nm = importdata('Par1.txt'); %torque data (Nm)

%Define Other parameters
d = 0.2; %wheel diameter (m)
r = d/2; %wheel radius (m)
B = 0.5; %Friction Co-eff. (constant)
m = 25; %Mass (Kg)
R_R = 20; %Reduction Ratio 
V = 24; %Voltage (V)
N = length(torque_Nm); %Length of the torque data
T = 15/1000; %Time (s)
f_sampling = 1/T; %Sampling Frequency
t = linspace(0,N-1,N)*T; %Time Vector
Torque_W = torque_Nm*R_R; %Wheel torque
TF_F_V = tf([1],[m B]); %Transfer function from force to velocity

%Calculate all the variables without filter
Force = Torque_W/r;
Velocity = lsim(TF_F_V,Force,t);
Angular_Velocity = Velocity/r;
Wheel_Speed = Angular_Velocity/(2*pi);
Wheel_RPM = Wheel_Speed*60;
Motor_RPM = Wheel_RPM*R_R;
Distance_Travel = cumtrapz(Velocity)*T;
Velocity_KMH = 3.6*Velocity;
Power = (Torque_W.*Angular_Velocity);
Current = (Power/24);

%plotting the variables without filter
figure('Name','Variables without filter')
subplot(3,2,1)
plot(t,Force)
title('Wheel thurst force(N):');
ylabel('Force');
xlabel('Time');
subplot(3,2,2)
plot(t,Motor_RPM)
title('Engine rotation speed(rpm):')
ylabel('Angular velocity');
xlabel('Time');
subplot(3,2,3)
plot(t,Velocity_KMH)
title('Linear speed(km/h):')
ylabel('Linear velocity');
xlabel('Time');
subplot(3,2,4)
plot(t,Distance_Travel)
title('Vehicle displacement(m):')
ylabel('Displacement');
xlabel('Time');
subplot(3,2,5)
plot(t,Power)
title('Power consumption(W):')
ylabel('Power');
xlabel('Time');
subplot(3,2,6)
plot(t,Current)
title('Supplied current(A):')
ylabel('Current');
xlabel('Time');

% Calculate the Fourier Transform of torque to find the frequency components
torque_fft = fft(torque_Nm);
vecfrec = (0:1:N-1) / (N * T); %vectors of the frequency

% Reduce the contents to useful information
torque_fft = torque_fft(1:N/2+1);
torque_fft = torque_fft / (N/2);
vecfrec = vecfrec(1:N/2+1);

% Plot the Fourier Transform of torque (Magnitude and Phase)
figure('Name','FFT of Torque Signal [Nm]')
subplot(211);
plot(vecfrec, abs(torque_fft));
title('Normalized Magnitude')
subplot(212);
plot(vecfrec, angle(torque_fft));
title('Phase [rad]')

% Filter Design: Second Order Butterworth Filter
fc = 2; % Cutoff frequency
[b_butter, a_butter] = butter(2, fc / (f_sampling / 2));

% Plot the frequency response of the filter
figure('Name', 'Frequency response')
freqz(b_butter, a_butter, [], f_sampling)

% Filter the torque signal
torque_lpf = filter(b_butter, a_butter, torque_Nm);

% Calculate and plot the Fourier Transform of the filtered torque signal
torque_lpf_fft = fft(torque_lpf);
torque_lpf_fft = torque_lpf_fft(1:N/2+1);
torque_lpf_fft = torque_lpf_fft / (N/2);
torque_lpf_fft(1) = torque_lpf_fft(1) / 2;

%plot FFT of the filtered torque signal
figure('Name', 'FFT filtered signal')
plot(vecfrec, abs(torque_lpf_fft));
title('FFT of filtered torque (Magnitude)')

% Plot the filtered and unfiltered torque signals
figure('Name', 'Filtered and Unfiltered torque')
title("Filtered and unfiltered torque signal [Nm]");
plot(t, torque_Nm, 'r')
hold on
plot(t, torque_lpf, 'b')
hold off
legend({'Unfiltered','Filtered'});

%calculate the variables with filter
Torque_w_filtered = torque_lpf*R_R; %Wheel torque
F_filtered = Torque_w_filtered/r;
v_filtered = lsim(TF_F_V,F_filtered,t);
w_filtered = v_filtered/r;
wheel_speed_filtered = w_filtered/(2*pi);
wheel_rpm_filtered = wheel_speed_filtered*60;
motor_rpm_filtered = wheel_rpm_filtered*R_R;
v_filtered_kmh = v_filtered*3.6;
s_filtered = cumtrapz(v_filtered)*T;
P_filtered = torque_lpf.*w_filtered;
I_filtered = P_filtered/v_filtered;

%plotting the variables with filter
figure('Name','Variables with filter')
subplot(3,2,1)
plot(t,F_filtered)
title('Wheel thurst force(N):');
ylabel('Force');
xlabel('Time');
subplot(3,2,2)
plot(t,motor_rpm_filtered)
title('Engine rotation speed(rpm):')
ylabel('Angular velocity');
xlabel('Time');
subplot(3,2,3)
plot(t,v_filtered_kmh)
title('Linear speed(km/h):')
ylabel('Linear velocity');
xlabel('Time');
subplot(3,2,4)
plot(t,s_filtered)
title('Vehicle displacement(m):')
ylabel('Displacement');
xlabel('Time');
subplot(3,2,5)
plot(t,P_filtered)
title('Power consumption(W):')
ylabel('Power');
xlabel('Time');
subplot(3,2,6)
plot(t,I_filtered)
title('Supplied current(A):')
ylabel('Current');
xlabel('Time');

