function [var]=constr(q,qd,param)
var=fort('constr',...
q,1,'d',qd,2,'d',param,3,'d',...
'sort',[36,1],4,'d')