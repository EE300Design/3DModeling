function  output = python_yoga(script)
    cmd1 = ['python ',script];
    commandStr = [cmd1];
    [~,output] = system(commandStr);
end