      subroutine xchar(line,k)
c     ======================================================================
c     routine systeme dependente  pour caracteres speciaux
c     ======================================================================
c effacement de la ligne : retourner  k>99
c fin de ligne : retourner k=99
c effacement du caractere precedent :retourner k=-1
c ignorer le caractere : retourner k=0
c
      include '../stack.h'
c
      integer blank
      integer k
      character line*(*)
      data blank/40/
c
      if(ichar(line(1:1)).eq.0) then
c     prise en compte de la marque de fin de chaine C
c     dans le cas d'un appel de matlab par un programme C
         k=99
      elseif(ichar(line(1:1)).eq.9) then
c     tab remplace par un blanc
         k=blank+1
      else
         call basout(io,wte,
     +        line(1:1)//' is not a scilab character')
         k=0
      endif
c
      end
