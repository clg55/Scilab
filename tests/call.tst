// Copyright INRIA
// Testing interface of programs put in SCIDIR/routines/default/Ex-fort.f
//
//                  Test 1
// ======================================================
// Corresponding to the following Fortran code inserted in 
// SCIDIR/routines/default/Ex-fort.f.
// 
//
//      subroutine foobar1(fname)
//      character*(*) fname
//      logical getrhsvar, createvar,  putlhsvar
//      include '../../routines/stack.h'
//c
//      nbvars=0
//      minrhs=5
//      maxrhs=5
//      minlhs=1
//      maxlhs=4
//c
//      if(.not.((rhs.ge.minrhs).and.(rhs.le.maxrhs))) then
//         call erro('wrong number of rhs arguments')
//         return
//      endif
//      if(.not.((lhs.ge.minlhs).and.(lhs.le.maxlhs))) then
//         call erro('wrong number of lhs arguments')
//         return
//      endif
//c     
//c     when using fort the first parameter is the function name 
//      if(.not.getrhsvar(1,'c',m1,n1,l1)) return
//      if(.not.getrhsvar(2,'c',m2,n2,l2)) return
//      if(.not.getrhsvar(3,'i',m3,n3,l3)) return
//      if(.not.getrhsvar(4,'r',m4,n4,l4)) return
//      if(.not.getrhsvar(5,'d',m5,n5,l5)) return
//c
//      if(.not.createvar(6,'d',m5,n5,l6)) return
//      if(.not.createvar(7,'d',m5,n5,l7)) return
//c
//      call foubare(cstk(l2:l2+m2*n2),istk(l3),n3*m3,sstk(l4),n4*m4,
//     $     stk(l5),m5,n5,stk(l6),stk(l7))
//c     
//      lhsvar(1)=3
//      lhsvar(2)=4
//      lhsvar(3)=5
//      lhsvar(4)=6
//      if(.not.putlhsvar()) return
//c     
//      end
//
//Routine call in Scilab
x =[1,2,3];y =[1,2,3;4,5,6];z=[10,11;12,13];
[a,b,c,d]=call('foobar1','mul', x, y, z);
// tests 
if norm(a-2*x,1) > %eps then pause,end
if norm(b-2*y,1) > %eps then pause,end
if norm(c-2*z,1) > %eps then pause,end
[mc,nc]=size(c);
w=zeros(c);
for i=1:mc;for j=1:nc, w(i,j)=i+j;end;end
if norm(d-(2*z.*w),1) > %eps then pause,end

[a,b,c,d]=call('foobar1','add', x, y, z);
if norm(a-(2+x),1) > %eps then pause,end
if norm(b-(2+y),1) > %eps then pause,end
if norm(c-(2+z),1) > %eps then pause,end
w=zeros(c);
for i=1:mc;for j=1:nc, w(i,j)=i+j;end;end
if norm(d-(2+z+w),1) > %eps then pause,end
//
//
//             Test 2
// ======================================================
// Routine foubare is in SCIDIR/default/Ex-fort.f
// and "foubare" appears in SCIDIR/default/Flist
// This is equivalent to -->link("foobar.o","foubare");
// Routine call from scilab:

a =[1,2,3];b =[1,2,3;4,5,6];c =[10,11;12,13];
[ma,na]=size(a);ia=ma*na;
[mb,nb]=size(b);ib=mb*nb;
[mc,nc]=size(c);ic=mc*nc;
md=mc;nd=nc;
[as,bs,cs,ds]=call('foubare','mul',1,'c',a,2,'i',ia,3,'i',b,4,'r',ib,5,'i',...
                            c,6,'d',mc,7,'i',nc,8,'i',...
                   'out',[ma,na],2,'i',[mb,nb],4,'r',[mc,nc],6,'d',...
                          [md,nd],9,'d',[mc,nc],10,'d');
if norm(as-2*a,1) > %eps then pause,end
if norm(bs-2*b,1) > %eps then pause,end
if norm(cs-2*c,1) > %eps then pause,end
[mc,nc]=size(c);
w=zeros(c);
for i=1:mc;for j=1:nc, w(i,j)=i+j;end;end
if norm(ds-(2*c.*w),1) > %eps then pause,end

md=mc;nd=nc;
[as,bs,cs,ds]=call('foubare','add',1,'c',a,2,'i',ia,3,'i',b,4,'r',ib,5,'i',...
                            c,6,'d',mc,7,'i',nc,8,'i',...
                   'out',[ma,na],2,'i',[mb,nb],4,'r',[mc,nc],6,'d',...
                          [md,nd],9,'d',[mc,nc],10,'d');
if norm(as-(2+a),1) > %eps then pause,end
if norm(bs-(2+b),1) > %eps then pause,end
if norm(cs-(2+c),1) > %eps then pause,end
[mc,nc]=size(c);
w=zeros(c);
for i=1:mc;for j=1:nc, w(i,j)=i+j;end;end
if norm(ds-(2+c+w),1) > %eps then pause,end

//other valid call (output parameters 1 3 and 5 are also inputs)
a =[1,2,3];b =[1,2,3;4,5,6];c =[10,11;12,13];md=mc;nd=nc;mul=str2code('mul');
[as,bs,cs,ds]=call('foubare','mul',1,'c',a,2,'i',ia,3,'i',b,4,'r',ib,5,'i',...
                            c,6,'d',mc,7,'i',nc,8,'i',...
                   'out',2,4,6,...
                          [md,nd],9,'d',[mc,nc],10,'d');
if norm(as-2*a,1) > %eps then pause,end
if norm(bs-2*b,1) > %eps then pause,end
if norm(cs-2*c,1) > %eps then pause,end
[mc,nc]=size(c);
w=zeros(c);
for i=1:mc;for j=1:nc, w(i,j)=i+j;end;end
if norm(ds-(2*c.*w),1) > %eps then pause,end


