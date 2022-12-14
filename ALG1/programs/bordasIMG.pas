program bordasIMG;
const
	MAX=512;
	LIMIAR=20;
	PRETO=0;
	BRANCO=255;
type
	tpimagem = array[1..MAX, 1..MAX] of longint;
var
	im,mb:tpimagem;
	numlin,numcol,nummax: longint;
procedure leimagem (var im:tpimagem;var numlim,numcol,nummax:longint);
var
	id:string[10];
	i,j:longint;
begin
	readln(id);
	readln(numcol,numlim);
	readln(nummax);
	for i:=1 to numlin do 
		for j:=1 to numcol do 
			read(im[i,j]);
end;
procedure detectabordas (var m,mb:tpimagem;numlin,numcol:longint);
var
	i,j:longint;
begin
	for i:= 2 to numlin-1 do
		for j:=2 to numcol-1 do
			if abs(m[i,j]*4-(m[i-1,j]+m[i+1,j]+m[i,j+1]+m[i,j-1])) > LIMIAR then
				mb[i,j]:=BRANCO
			else
				mb[i,j]:=PRETO;
end;				
procedure escreveimagem (var im:tpimagem;var numlin,numcol,nummax:longint);
var
	i,j:longint;
begin
	writeln('P2');
	writeln(numcol:5,numlin:5);
	writeln(nummax);
	for i:=1 to numlin do 
		for j:=1 to numcol do 
			writeln(im[i,j]); 
end;
begin
	leimagem(im,numlin,numcol,nummax);
	detectabordas(im,mb,numlin,numcol);
	escreveimagem(mb,numlin,numcol,nummax);
end.
