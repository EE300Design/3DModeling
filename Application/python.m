function  output = python(script,input)
    
    commandStr = ['python3 ',script,' ',input];
    [~,output] = system(commandStr);
end 