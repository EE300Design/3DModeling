function [X,Y,Z] = format_stl(stl_vertices)
    count = 0;
    for i = 1:3:length(stl_vertices)
        count = count+1;
        X(:,count) = stl_vertices(i)';
        Y(:,count) = stl_vertices(i+1)';
        Z(:,count) = stl_vertices(i+2)';
    end
end