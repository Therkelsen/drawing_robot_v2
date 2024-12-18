clc; clear; close all;

yp = 7;
xp = 0,
L = 5;
q1 = atan2(yp, xp) + acos((xp^2 + yp^2)/(2*L*sqrt(xp^2 + yp^2)))
q2 = atan2(yp, xp) - acos((xp^2 + yp^2)/(2*L*sqrt(xp^2 + yp^2)))

q1deg = q1*180/pi
q2deg = q2*180/pi

% Given parameters
L = 5;  % Link length
q1_vals = linspace(0, pi, 100);  % Joint 1 angles (range -pi to pi)
q2_vals = linspace(0, pi, 100);  % Joint 2 angles (range -pi to pi)

% Initialize matrix to store end-effector positions (xp, yp)
[x_p, y_p] = deal([]);

% Loop over the joint angles q1 and q2 to compute the workspace
for q1 = q1_vals
    for q2 = q2_vals
        % Forward kinematics equations to compute xp, yp
        xp_current = L * cos(q1) + L * cos(q2);
        yp_current = L * sin(q1) + L * sin(q2);
        
        % Store the end-effector positions
        x_p = [x_p, xp_current];
        y_p = [y_p, yp_current];
    end
end

% Plot the Cartesian workspace
figure;
scatter(x_p, y_p, 100, 'filled', 'MarkerFaceColor', 'b');
title({'Reachable Workspace in Cartesian Coordinates',''});
xlabel('X Position (xp)');
ylabel('Y Position (yp)');
axis equal;
grid on;

% Optional: Add a circular boundary representing the maximum reach
theta = linspace(0, 2*pi, 100);
circle_x = L * (cos(theta) + cos(theta));
circle_y = L * (sin(theta) + sin(theta));
hold on;
plot(circle_x, circle_y, 'r--', 'LineWidth', 1.5);
legend('Reachable', 'Max Reach', 'Location', 'Best');