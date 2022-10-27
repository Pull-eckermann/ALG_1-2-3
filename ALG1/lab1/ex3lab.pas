program ex3;
var
	nota, lim1, lim2, lim3: real;
	N, contA, contB, contC, contD: integer;
begin
	writeln('escreva seus limites em ordem decrescente');	
	read(lim1, lim2, lim3);
	read(N); 
	cont:= 0;
	contA:= 0;
	contB:= 0;
	contC:= 0;
	contD:= 0;
	while cont < N do	
	begin
		read(nota);			
		if nota >= lim1 then
			contA:= contA + 1
		else if nota >= lim2 then
			contB:= contB + 1
		else if nota >= lim3 then
			contC:= contC + 1
		else
			contD:= contD + 1;
		cont:= cont + 1;
	end;
	writeln(
	 

