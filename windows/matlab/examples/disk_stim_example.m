function disk_stim_example
% DISK_STIM_EXAMPLE - a simple example showing how to use the mcc_ssr08
% interface to send stimulus patterns.
%
% Note, this program assumes the command id 1 is the move to start command
% and the command ids 2,..,6 are stimulus patterns.
%
% This program also assumes the board number is 0.
%
% The pasue after sending the stimulus command is required as the software
% has no way to known when the given command has been completed. it is up
% to the user to set this correctly. 
%
% It is good practice to set all lines to low after trigger a given
% pattern. This should be done after a suitable pause time. If this is not
% done it is not possible to trigger the same pattern twice in a row.
%

board_num = 0;
move2start_id = 1;
stimulus_id_array = [2:6];
num_trials = 1;
move2start_pause_t = 4.0;
stimulus_pause_t = 3.0;

% Loop over number of trials
for i = 1:num_trials
    
    fprintf('trial %d\n',i);
    
    % Loop over stimulus ids
    for id = stimulus_id_array
        
        fprintf('moving to start position\n');
        mcc_ssr08(board_num, 'setvalue', move2start_id);
        pause(move2start_pause_t);
        mcc_ssr08(board_num, 'alllo'); % Return all lines to low
        
        fprintf('running stimulus id %d\n', id);
        mcc_ssr08(board_num, 'setvalue', id);
        pause(stimulus_pause_t);
        mcc_ssr08(board_num, 'alllo'); % Return all lines to low
        
    end
end

fprintf('moving to start position\n');
mcc_ssr08(board_num, 'setvalue', move2start_id);
pause(move2start_pause_t);
mcc_ssr08(board_num, 'alllo'); % Return all lines to low

