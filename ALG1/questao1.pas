program printPrimo;
function ehPrimo(num:longint): boolean;
var
	i:longint;
begin
	i:= 2;
	ehPrimo:= true;
	while (i <= num div 2) and ehPrimo do
	begin	
		if num mod i = 0 then
			ehPrimo:= false;
		i:= i +1;
	end;
end;
var
	n,m: longint;
begin
	read(n);
	for m:=2 to n do
		if ehPrimo(m) then
			writeln(m);
end.
			
	
