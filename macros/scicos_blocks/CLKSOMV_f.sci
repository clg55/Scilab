function [x,y,typ]=CLKSOMV_f(job,arg1,arg2)
x=[];y=[];typ=[];
p=1 //pixel sizes ratio
select job
case 'plot' then
  [orig,sz]=arg1(1:2)
  graphics=arg1(2); [orig,sz,orient]=graphics(1:3)
  thick=xget('thickness');xset('thickness',2)
  dash=xget('dashes');xset('dashes',default_color(-1))
  rx=sz(1)*p/2
  ry=sz(2)/2
  xarc(orig(1),orig(2)+sz(2),sz(1)*p,sz(2),0,360*64)
  xsegs(orig(1)+rx*[1/2.3 1;2-1/2.3 1],orig(2)+ry*[1 2-1/2.3;1,1/2.3],0)
  xset('thickness',thick);
  out= [-1/14  0
      0      -1/7
      1/14   0]*3
  xfpoly(sz(1)*out(:,1)+orig(1)+sz(1)/2,sz(2)*out(:,2)+orig(2),1)
  xset('dashes',dash)
case 'getinputs' then
  graphics=o(2)
  [orig,sz,orient]=graphics(1:3)
  t=[3*%pi/2 0 %pi/2]
  r=sz(2)/2
  rx=r*p
  x=(rx*sin(t)+(orig(1)+rx)*ones(t))
  y=r*cos(t)+(orig(2)+r)*ones(t)
  typ=-ones(x)
case 'getoutputs' then
  graphics=o(2)
  [orig,sz,orient]=graphics(1:3)
  t=%pi
  dy=sz(2)/7
  r=sz(2)/2
  rx=r*p
  x=(rx*sin(t)+(orig(1)+rx)*ones(t))
  y=r*cos(t)+(orig(2)+r)*ones(t)+dy
  typ=-ones(x)
case 'getorigin' then
  [x,y]=standard_origin(arg1)
case 'set' then
  x=arg1;
  x(3)(11)=[]//compatibility
case 'define' then
  model=list('sum',[],[],[1;1;1],1,[],[],[],[],'d',-1,[%f %f],' ',list())
  x=standard_define([1 1]/1.2,model,[],[])
end




