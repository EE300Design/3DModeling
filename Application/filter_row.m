function r_row = filter_row(row)
    r_row = row;
    errors = (row<2)+(row>20);
    inv_errors = ~errors;

    errors = (1:length(errors)).*errors;
    errors = errors(errors>0);
    inv_errors = (1:length(inv_errors)).*inv_errors;
    inv_errors = inv_errors(inv_errors>0);

    r_row(errors) = mean(row(inv_errors));
end