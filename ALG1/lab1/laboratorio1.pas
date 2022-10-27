program laboratorio1;
	var
	s,h,m:longint;
	begin
		read(s);
		h:= s div 3600;
		s:= s mod 3600;
		m:= s div 60;
		s:= s mod 60 ;
		writeln(h , 'horas_' , m , 'minutos_' , s , 'segundos_');
	end.

