function [x,y,typ]=ABSBLK_f(job,arg1,arg2)
x=[];y=[];typ=[];
select job
case 'plot' then
  standard_draw(arg1)
  graphics=arg1(2); 
  [orig,sz]=graphics(1:2)
  xstringb(orig(1),orig(2),'Abs',sz(1),sz(2),'fill')
case 'getinputs' then
  [x,y,typ]=standard_inputs(arg1)
case 'getoutputs' then
  [x,y,typ]=standard_outputs(arg1)
case 'getorigin' then
  [x,y]=standard_origin(arg1)
case 'set' then
  x=arg1;
  graphics=arg1(2);label=graphics(4)
  model=arg1(3);  nin=model(2)
  [ok,label,nin1]=getvalue('Set Abs block parameters',..
      ['Block label';'Number of inputs (outputs)'],..
      list('str',1,'vec',1),..
      [label;sci2exp(nin)])
  if ok then 
    if nin1 > 0 then
      nin=nin1
      [model,graphics,ok]=check_io(model,graphics,nin,nin,0,0)
      graphics(4)=label
      model(2)=nin;model(3)=nin;
      x(2)=graphics;x(3)=model
    else	
      x_message('Number of inputs must be positive')
    end
  end
case 'define' then
  model=list('absblk',1,1,0,0,[],[],[],[],'c',%f,[%t %f])
  x=standard_define([2 2],model)
end
