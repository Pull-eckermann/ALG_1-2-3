program laboratorio2new;
	var
	n,soma,soma1,soma2,soma3:integer;
	begin
		soma:= 0;
		soma1:= 0;
		soma2:= 0;
		soma3:= 0;
		read(n);
		while n <>0 do
		begin
			if n mod 3 = 0 then
				if n mod 7 = 0 then			
					soma:= soma + 1 				
				else
					soma1:= soma1 + 1
			else
				if n mod 7 = 0 then
					soma2:= soma2 + 1
				else
					soma3:= soma3 + 1;		
			read(n);
		end;
		writeln(soma , '_condiçao1');
		writeln(soma1 , '_condiçao2');
		writeln(soma2 , '_condiçao3');
		writeln(soma3 , '_condiçao4');
	end.		 
		
