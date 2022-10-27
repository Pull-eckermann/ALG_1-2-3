(* JOGO: campo minado
 *  O jogador seleciona uma posicao do tabuleiro.
 *  Se esta posicao contiver uma bomba, o jogo termina.
 *  Caso contrario, esta posicao e todas as vizinhas que contiverem 0 bombas
 *  vizinhas sao abertas.
 *)
program campoMinado;

USES CRT;

CONST
   MAX	    = 20;   (* dimensao da matriz quadrada *)
   MAXPILHA = MAX*MAX;
   ERRO	    = 0;
   OK	    = 1;

   VBOMBA =  -1; (* valor na matriz que marca a existencia de bomba *)
   FECHADO   = ' _';

TYPE
   TpCelula = record
		 nBombas : integer;
		 aberto	 : boolean;
		 marcado : boolean;
	      end;	 
   TpMatriz = array [0..MAX+1,0..MAX+1] of TpCelula; (* tabuleiro *)
   TpJogo   = record
		 nLin, nCol : integer;
		 nBombas    : integer;
		 m	    : TpMatriz;
	      end;	    
   
   TpPosicao = record
		  lin, col : integer;
	       end;	   
   TpItem    = TpPosicao;
   TpPilha   = record
		  item : array[1..MAX*MAX] of TpItem;
		  topo : integer;
	       end;    

var
   j			    : TpJogo;
   pos			    : TpPosicao;
   sair, perdeu		    : boolean;
   nCelAberto, celParaAbrir : integer;

   cor			    :array [-1..8] of integer =
   (Red, White, Yellow, Green, Cyan, Magenta, Brown, LightGray,
    LightGreen, LightRed);

   letra                    :array[-1..8] of string[2] =
   (' *', '  ', ' 1', ' 2', ' 3', ' 4', ' 5', ' 6', ' 7', ' 8');

(*-----------------------------------------------------------------------
 * TAD Pilha
 *)
procedure criaPilha( var p: TpPilha );
begin
  p.topo:= 0;
end;

function pilhaVazia( p: TpPilha ): boolean;
begin
  pilhaVazia:= p.topo = 0;
end;

function empilha( var p: TpPilha; item: TpItem ): integer;
begin
  if p.topo = MAXPILHA then
    empilha:= ERRO
  else begin
     p.topo:= p.topo + 1;
     p.item[p.topo]:= item;
     empilha:= OK;
  end;
end;

function desempilha(var p : TpPilha; var item: TpItem ): integer;
begin
   if p.topo = 0 then
      desempilha:= ERRO
   else begin
      item:= p.item[p.topo];
      p.topo:= p.topo - 1;
      desempilha:= OK;
   end;
end; { desempilha }


(*-----------------------------------------------------------------------
 * Procedimentos para inicializacao do jogo
 * Gere os procedimentos/funcoes chamadas por criaJogo
 *)

procedure criaBombas (var j: TpJogo );
var
   l, c, i : integer;
begin
   randomize();
   i:= 0;
   while i < j.nBombas do
   begin
      l:= random(j.nLin) + 1;
      c:= random(j.nCol) + 1;
      if j.m[l,c].nBombas = 0 then
      begin
	 j.m[l,c].nBombas:= VBOMBA;
	 i:= i+1;
      end;
   end;
end; { criaBombas }

procedure zeraTabuleiro(var j:TpJogo);
var
   l,c: integer;
begin
   for l:=1 to j.nLin + 1 do
      for c:=0 to j.nCol + 1 do
         j.m[l,c].nBombas:= 0;
         j.m[l,c].aberto:= false;
         j.m[l,c].marcado:= false;
end;

(* zera o tabuleiro para começar um novo jogo*) 

procedure contaVizinhos(var jooj: TpJogo);
var
   l,c,cont,i,k: integer;
begin
   for l:=1 to jooj.nLin do
      for c:=1 to jooj.nCol do 
         if jooj.m[l,c].nBombas <> VBOMBA then
         begin
            cont:= 0;
            for i:= l-1 to l+1 do
               for k:=c-1 to c+1 do
                  if jooj.m[i,k].nBombas = VBOMBA then
                     cont:= cont + 1;
            jooj.m[l,c].nBombas:= cont;
         end;
end;

(*atribui o numero de bombas vizinas a cada célula*)
 
procedure criaJogo(var j: TpJogo);
begin
   writeln('Entre com numero de linhas, colunas e bombas (max= ', MAX, '):');
   readln (j.nLin, j.nCol, j.nBombas);
   zeraTabuleiro( j );
   criaBombas( j );
   contaVizinhos( j );
end; { criaJogo }

(*-----------------------------------------------------------------------
 Imprime a matriz de cores, usa a biblioteca CRT para limpar a tela e para 
 imprimir o conteudo da matriz de forma colorida.
*)

procedure mostraJogo(j: TpJogo);
var
   l, c	: integer;
begin
   clrscr; 
   for l:= 0 to (j.nCol+1)*2 do
      write('#');
   writeln;
   
   for l:= 1 to j.nLin do
   begin
      write('#');

      for c:= 1 to j.nCol do
      begin
	 if not j.m[l,c].aberto then
	 begin
	    textcolor( white );
	    write( FECHADO );
	 end
	 else begin
	    textcolor( cor[j.m[l,c].nBombas] );
	    write( letra[j.m[l,c].nBombas] );
	 end;
      end;

      textcolor( White );
      writeln(' #');
   end;

   for l:= 0 to (j.nCol+1)*2 do
      write('#');
   writeln;
end; { mostraJogo }

(*-----------------------------------------------------------------------
 Abre todas as celulas do tabuleiro para mostrar no final
 *)
procedure abreTudo (var j : TpJogo );
var
   l, c	: integer;
begin
   for l:= 1 to j.nLin do
      for c:= 1 to j.nCol do
	 j.m[l,c].aberto:= true;
end;

(* --------------------------------------------------------------------
 * Abre a celula na posical 'pos'.  Para todas as celulas abertas,
 *  todos os seus vizinhos que tem zero  bombas ao seu redor tambem
 *  devem ser abertas.
 *)

function abreCelula(var j : TpJogo; pos: TpPosicao ): integer;
begin







end; { abreCelula }

(* --------------------------------------------------------------------
 * Le uma posicao a ser aberta.
 * linha=0 e coluna=0 indica fim de jogo
 * Verificar se o numero da linha e coluna sao validas
 *)
procedure lePosicao(j : TpJogo; var pos : TpPosicao);
begin
   repeat
function posFechada( j: TpJogo; pos: TpPosiçao): boolean;
begin
   posFechada:= not j.m[pos.lin, pos.col].aberto;
end;
      writeln;
      write('Entre linha e coluna: ');
      readln( pos.lin, pos.col );
   until (pos.lin >= 0) and (pos.lin <= j.nLin) and
         (pos.col >= 0) and (pos.col <= j.nCol);
end;

function posFechada( j: TpJogo; pos: TpPosicao): boolean;
begin
   posFechada:= not j.m[pos.lin, pos.col].aberto;
end;

(*-----------------------------------------------------------------------
 Programa principal
*)

begin
   criaJogo( j );
   celParaAbrir:= j.nLin * j.nCol - j.nBombas;
   sair:= false;
   perdeu:= false;
   REPEAT
      mostraJogo ( j );
      lePosicao( j, pos );
      if (pos.lin = 0) and (pos.col = 0) then
	 sair:= true
      else if posFechada( j, pos ) then
      begin
	 nCelAberto := abreCelula(j, pos );
	 celParaAbrir:= celParaAbrir - nCelAberto;
	 if nCelAberto = 0 then
	    perdeu:= true;
      end
   UNTIL sair or perdeu or (celParaAbrir = 0);
   abreTudo( j );
   mostraJogo( j );
   writeln;
   if celParaAbrir = 0 then
      writeln('Parabens!! Voce venceu!!')
   else if perdeu then
      writeln('Voce perdeu...');
end.

