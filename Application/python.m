function  output = python(script)
    
    cmd1 = 'cd /Users/erikhuuki/miniconda3;';
    cmd2 = 'source ./bin/activate;';
    cmd3 = 'conda activate EE300;';
    cmd4 = 'cd /Users/erikhuuki/Library/CloudStorage/OneDrive-ThePennsylvaniaStateUniversity/EE300/3D-modeling-code/Application;';
    cmd5 = ['python3 ',script];
    
    commandStr = [cmd1,cmd2,cmd3,cmd4,cmd5];
    [~,output] = system(commandStr);
end