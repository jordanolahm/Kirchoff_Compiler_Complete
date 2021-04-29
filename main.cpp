#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<sstream>

using namespace std;

class PalReservada{
	public:
		string Palavra;
		string Token;
};

class Variaveis{
	public:
		string circuito;
		string nomeVar, tipoComponente, tipoSaida, nomeNo1, nomeNo2;
		float valCompAmp, valIni, frequencia; 
};

class No{
	public:
		string circuito;
		string nomeNo;
};

class StringArm{
	public:
		vector <string> listaStrings;
};

class MatrizSaida{
	public:
		string circuito;
		vector <string> nos;
		string**matrizSaida;
};

class ArvoreExpr{
	public:
		bool Operador;
		ArvoreExpr*DirFilho;
		ArvoreExpr*EsqFilho;
		string Conteudo;
};

ArvoreExpr*SeparaExpr(ArvoreExpr*Arvore, string Expr, int linha)
{
	if(Expr[0] != '(' && Expr[Expr.length() - 1] != ')')
	{
		ofstream ArquivoErros("Erro.txt", ios::app);
		ArquivoErros << "ERRO NA LINHA " << linha << " -SUGESTÃO: PARENTESES NAO BALANCEADOS" << endl;
		ArquivoErros.close();
		return NULL;
	}
	
	int cont, ControleParenteses;
	for(cont = 0, ControleParenteses = 0; cont < Expr.length(); cont++)
	{
		if(Expr[cont] == '(' || Expr[cont] == ')')
		{
			if(Expr[cont] == '(')
				ControleParenteses++;
			else if(Expr[cont] == ')')
				ControleParenteses--;
		}
	}
	if(ControleParenteses != 0)
	{
		ofstream ArquivoErros("Erro.txt", ios::app);
		ArquivoErros << "ERRO NA LINHA " << linha << " -SUGESTÃO: PARENTESES NAO BALANCEADOS" << endl;
		ArquivoErros.close();
		return NULL;
	}
	
	cout << Expr << endl;
	if(Expr[1] == '_' || Expr[1] == '#')
	{
		Arvore->Operador = false;
		Arvore->DirFilho = NULL;
		Arvore->EsqFilho = NULL;
		int contE = Expr.length() - 1;
		while(Expr[contE] == ')')
			contE--;
		string st = Expr.substr(0, contE + 2);
		Arvore->Conteudo = st;
		return Arvore;
	}
	else if(Expr[1] >= 48 && Expr[1] <= 57)
	{
		Arvore->Operador = false;
		Arvore->DirFilho = NULL;
		Arvore->EsqFilho = NULL;
		int contE = Expr.length() - 1;
		while(Expr[contE] == ')')
			contE--;
		string st = Expr.substr(0, contE + 2);
		Arvore->Conteudo = st;
		return Arvore;
	}
	else
	{
		int  cont, ControleParenteses;
		for(cont = 1, ControleParenteses = 0; cont < Expr.length(); cont++)
		{
			if(Expr[cont] == '(' || Expr[cont] == ')')
			{
				if(Expr[cont] == '(')
					ControleParenteses++;
				else if(Expr[cont] == ')')
					ControleParenteses--;
			}
			else if(Expr[cont] == '&' && ControleParenteses == 0)
			{
				Arvore->Operador = false;
				Arvore->DirFilho = NULL;
				Arvore->EsqFilho = NULL;
				Arvore->Conteudo = Expr;
				return Arvore;
			}
			else if((Expr[cont] == '+' || Expr[cont] == '-' || Expr[cont] == '*' || Expr[cont] == '/' || Expr[cont] == '>' || Expr[cont] == '<') && ControleParenteses == 0)
			{
				string AuxStrEsq, AuxStrDir;
				
				for(int cont2 = 1; cont2 < cont - 1; cont2++)
				{
					AuxStrEsq += Expr[cont2];
				}
				
				for(int cont2 = cont + 2; cont2 < Expr.length() - 1; cont2++)
				{
					AuxStrDir += Expr[cont2];
				}
				
				ArvoreExpr*noDir = new ArvoreExpr();
				ArvoreExpr*noEsq = new ArvoreExpr();
				Arvore->Operador = true;
				Arvore->DirFilho = SeparaExpr(noDir, AuxStrDir, linha);
				Arvore->EsqFilho = SeparaExpr(noEsq, AuxStrEsq, linha);
				Arvore->Conteudo = Expr[cont];
				return Arvore;
			}
			else if((Expr[cont] == 'O' || Expr[cont] == 'A' || (Expr[cont] == '=' && Expr[cont + 1] == '=') || (Expr[cont] == '=' && Expr[cont + 1] == '!') || (Expr[cont] == '=' && Expr[cont + 1] == '>') || (Expr[cont] == '=' && Expr[cont + 1] == '<') ) && ControleParenteses == 0)
			{
				string AuxStrEsq, AuxStrDir;
				
				if(Expr[cont] == 'O' || (Expr[cont] == '=' && Expr[cont + 1] == '=') || (Expr[cont] == '=' && Expr[cont + 1] == '!') || (Expr[cont] == '=' && Expr[cont + 1] == '>') || (Expr[cont] == '=' && Expr[cont + 1] == '<'))
				{
					for(int cont2 = 1; cont2 < cont - 1; cont2++)
					{
						AuxStrEsq += Expr[cont2];
					}
				
					for(int cont2 = cont + 3; cont2 < Expr.length() - 1; cont2++)
					{
						AuxStrDir += Expr[cont2];
					}
					Arvore->Conteudo = Expr[cont];
					Arvore->Conteudo += Expr[cont + 1];
				}
				else if(Expr[cont] == 'A')
				{
					for(int cont2 = 1; cont2 < cont - 1; cont2++)
					{
						AuxStrEsq += Expr[cont2];
					}
				
					for(int cont2 = cont + 4; cont2 < Expr.length() - 1; cont2++)
					{
						AuxStrDir += Expr[cont2];
					}
					
					Arvore->Conteudo = Expr[cont];
					Arvore->Conteudo += Expr[cont + 1];
					Arvore->Conteudo += Expr[cont + 2];
				}
				
				ArvoreExpr*noDir = new ArvoreExpr();
				ArvoreExpr*noEsq = new ArvoreExpr();
				Arvore->Operador = true;
				Arvore->DirFilho = SeparaExpr(noDir, AuxStrDir, linha);
				Arvore->EsqFilho = SeparaExpr(noEsq, AuxStrEsq, linha);
				return Arvore;
			}
		}
		
		if(ControleParenteses != 0)
		{
			ofstream ArquivoErros("Erro.txt", ios::app);
			ArquivoErros << "ERRO NA LINHA " << linha << " -SUGESTÃO: OPERADOR NAO ENCONTRADO" << endl;
			ArquivoErros.close();
			return NULL;
		}
	}	
}

void printaArvore(ArvoreExpr*Arvore)
{
	cout << Arvore->Conteudo << endl;
	
	if(Arvore->EsqFilho != NULL)
		printaArvore(Arvore->EsqFilho);
	if(Arvore->DirFilho != NULL)
		printaArvore(Arvore->DirFilho);
}

void arquivoExpressoes(int cont, ArvoreExpr*Arvore, string nomeArquivo)
{
	ofstream ArquivoIntermediarioExpressao(nomeArquivo.c_str(), ios::app);
	
	if(Arvore->Operador == false)
	{
		ArquivoIntermediarioExpressao << "expr" << cont << " = " << Arvore->Conteudo;
		ArquivoIntermediarioExpressao.close();
	}
	else if(Arvore->EsqFilho->Operador == true && Arvore->DirFilho->Operador == true)
	{
		ArquivoIntermediarioExpressao << "expr" << cont << " = " << "expr" << 2*cont + 1 << ' ' << Arvore->Conteudo << " expr" << 2*cont + 2 << endl;
		ArquivoIntermediarioExpressao.close();
		arquivoExpressoes(2*cont + 1, Arvore->EsqFilho, nomeArquivo);
		arquivoExpressoes(2*cont + 2, Arvore->DirFilho, nomeArquivo);
	}
	else if(Arvore->EsqFilho->Operador != true && Arvore->DirFilho->Operador == true)
	{
		ArquivoIntermediarioExpressao << "expr" << cont << " = " << Arvore->EsqFilho->Conteudo << ' ' << Arvore->Conteudo << " expr" << 2*cont + 2 << endl;
		ArquivoIntermediarioExpressao.close();	
		arquivoExpressoes(2*cont + 2, Arvore->DirFilho, nomeArquivo);	
	}
	else if(Arvore->EsqFilho->Operador == true && Arvore->DirFilho->Operador != true)
	{
		ArquivoIntermediarioExpressao << "expr" << cont << " = " << "expr" << 2*cont + 1 << ' ' << Arvore->Conteudo << ' ' << Arvore->DirFilho->Conteudo << endl;
		ArquivoIntermediarioExpressao.close();
		arquivoExpressoes(2*cont + 1, Arvore->EsqFilho, nomeArquivo);
	}
	else if(Arvore->EsqFilho->Operador != true && Arvore->DirFilho->Operador != true)
	{
		ArquivoIntermediarioExpressao << "expr" << cont << " = " << Arvore->EsqFilho->Conteudo << ' ' << Arvore->Conteudo << ' ' << Arvore->DirFilho->Conteudo << endl;
		ArquivoIntermediarioExpressao.close();
	}
}

int encontraCircuitoMatriz(vector <MatrizSaida> Matriz, string nomeCircuito)
{
	int cont;
	for(cont = 0; cont < Matriz.size(); cont++)
	{
		if(Matriz[cont].circuito == nomeCircuito)
			break;
	}
	
	if(cont == Matriz.size())
		return -1;
	
	return cont;
}

int encontraNoMatriz(vector <MatrizSaida> Matriz, string nomeCircuito, string no)
{
	int cont, cont2;
	for(cont = 0; cont < Matriz.size(); cont++)
	{
		for(cont2 = 0; cont2 < Matriz[cont].nos.size(); cont2++)
		{
			if(Matriz[cont].nos[cont2] == no && Matriz[cont].circuito == nomeCircuito)
				return cont2;
		}
	}
	return -1;
}

int main(int argc, char** argv) {
	
	string nomeArquivoFonte = "fonte.txt";
	string nomeArquivoPalRes = "PalRes.txt";
	string nomeArquivoTokens = "Tokens.txt";
	string nomeArquivoErro = "Erro.txt";
	string nomeArquivoIntermediario = "CodigoIntermediarioCircuitos.txt";
	string nomeArquivoIntermediarioExecucao = "CodigoIntermediarioExecucao.txt";
	ifstream CodigoFonte(nomeArquivoFonte.c_str());
	ifstream ArquivoPalavrasReservadas(nomeArquivoPalRes.c_str());
	ofstream ArquivoTokens(nomeArquivoTokens.c_str());
	ofstream ArquivoErros(nomeArquivoErro.c_str());
	ofstream ArquivoIntermediario(nomeArquivoIntermediario.c_str());
	ofstream ArquivoIntermediarioExecucao(nomeArquivoIntermediarioExecucao.c_str());

	
	vector <PalReservada> ListaPalReservadas;
	vector <Variaveis> ListaVariaveis;
	vector <No> Nos;
	vector <string> expressoes;
	vector <int> expressoesLinha;
	string auxString, auxNumString;
	stringstream auxSS;
	int contLinha = 0;
	
	bool ErroParte1 = false;
	bool ErroParte2 = false;
	
	while(!ArquivoPalavrasReservadas.eof())
	{
		PalReservada auxStruct;
		getline(ArquivoPalavrasReservadas, auxString, '\t');		
		getline(ArquivoPalavrasReservadas, auxStruct.Palavra, '\t');
		getline(ArquivoPalavrasReservadas, auxStruct.Token);
		getline(ArquivoPalavrasReservadas, auxString);
		ListaPalReservadas.push_back(auxStruct);
	}

	bool comentario = false;	//CONTROLE DE COMENTARIOS
	bool declaracao = true;		//CONTROLE DE DECLARACAO
	bool declaracaoNo = true;
	bool primeiroNo = false;
	string nomeCirc = "NONE";
	int aux;    
	
//Analise sintatica
while(!CodigoFonte.eof())
{
	contLinha++;
	getline(CodigoFonte, auxString);
	for(int cont = 0; cont < auxString.length(); cont++)
	{
		//ELIMINACAO DE COMENTARIOS
		if(auxString[cont] == '$' && comentario == false)
		{
			comentario = true;
		}
		else if(comentario == true)
		{
			if(auxString[cont] == '$')
				comentario = false;
		}
		
		//BLOCO DE DECLARACAO DE CIRCUITOS
		else if(declaracao == true)
		{
			if(auxString[cont] == 'C')
			{
				cont++;
				if(auxString[cont] == 'I')
				{
					cont++;
					if(auxString[cont] == 'R')
					{
						cont++;
						if(auxString[cont] == 'C')
						{
							cont++;
							if(auxString[cont] == 'D')
							{
								cont++;
								if(auxString[cont] == 'E')
								{
									cont++;
									if(auxString[cont] == 'F')
									{
										cont++;
										if(cont == auxString.length() || auxString[cont] == ' ')
										{
											ArquivoTokens << "<CIRCDEF,> ";
										}
										else if(auxString[cont] == '$')
										{
											ArquivoTokens << "<CIRCDEF,> ";
											comentario = true;
										}
										else
										{
											ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA NO CIRCDEF" << endl;
											ErroParte1 = true;
										}
										cont--;
									}
								}
							}
						}
					}
				}
			}
			
			else if(auxString[cont] == 'O')
			{
				cont++;
				if(auxString[cont] == 'U')
				{
					cont++;
					if(auxString[cont] == 'T')
					{
						cont++;
						if(auxString[cont] == 'D')
						{
							cont++;
							if(auxString[cont] == 'E')
							{
								cont++;
								if(auxString[cont] == 'F')
								{
									cont++;
									if(cont == auxString.length() || auxString[cont] == '[')
									{
										ArquivoTokens << "<OUTDEF,> ";
										declaracao = false;
									}
									else
									{
										ArquivoErros << "ERRO NA LINHA " << contLinha << "-SUGESTÃO: FORMATACAO ERRADA NO OUTDEF" << endl;
										ErroParte1 = true;
									}
									cont--;
								}
							}
						}
					}
				}
			}
			
			else if((auxString[cont] >= 97 && auxString[cont] <= 122) && nomeCirc == "NONE")
			{
				bool circuitoDeclarado = false;
				nomeCirc.clear();
				nomeCirc += auxString[cont];
				cont++;
				while(auxString[cont] >= 97 && auxString[cont] <= 122)
				{
					nomeCirc += auxString[cont];
					cont++;
				}
				
				for(int cont2 = 0; cont2 < Nos.size(); cont2++)
				{
					if(Nos[cont2].circuito == nomeCirc)
						circuitoDeclarado = true;
				}
				for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
				{
					if(ListaVariaveis[cont2].circuito == nomeCirc)
						circuitoDeclarado = true;
				}
				
				if(circuitoDeclarado == true)
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE CIRCUITOS -" << endl;
					ErroParte1 = true;
				}
				else
				{
					ArquivoTokens << "<DECLARATION,> ";
					declaracaoNo = true;
					primeiroNo = true;
				}
				cont--;
			}
			
			else if((auxString[cont] >= 97 && auxString[cont] <= 122) && declaracaoNo == true && nomeCirc != "NONE")
			{
				No noAux;
				noAux.circuito = nomeCirc;
				while(auxString[cont] >= 97 && auxString[cont] <= 122)
				{
					noAux.nomeNo += auxString[cont];
					cont++;
				}
				cont--;
				bool noDeclarado = false;
				for(int cont2 = 0; cont2 < Nos.size(); cont2++)
				{
					if(Nos[cont2].circuito == noAux.circuito && Nos[cont2].nomeNo == noAux.nomeNo)
						noDeclarado = true;
				}
				if(noDeclarado == true)
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE NOS -" << endl;
					ErroParte1 = true;
				}
				else
				{
					if(primeiroNo == true && noAux.nomeNo != "gnd")
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: O PRIMEIRO NO DECLARADO DEVE SER O GND" << endl;
					}
					else
					{
						Nos.push_back(noAux);
						primeiroNo = false;
						ArquivoTokens << "<NDECLARATION," << Nos.size() - 1 << "> ";
					}
				}
			}
			
			else if(auxString[cont] == ',')
			{
				ArquivoTokens << "<,,> ";
			}
			
			else if(auxString[cont] == ';' && declaracaoNo == true)
			{
				declaracaoNo = false;
				cont++;
				ArquivoTokens << "<;,> ";
			}
			
			else if(auxString[cont] == ';' && declaracaoNo == false)
			{
				declaracaoNo = true;
				cont++;
				ArquivoTokens << "<;,> ";
			}
			
			else if(auxString[cont] == '(' && declaracaoNo == false)
			{
				bool componenteDeclarado = false;
				cont++;
				if(auxString[cont] == 'C')
				{
					cont++;
					if(auxString[cont] == 'S')
					{
						cont++;
						if(auxString[cont] == 'R')
						{
							cont++;
							if(auxString[cont] == ',')
							{
								Variaveis auxVariavel;
								auxVariavel.circuito = nomeCirc;
								auxVariavel.tipoComponente = "CSR";
								
								cont++;
								int iniCont = cont + 1;	
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CSR -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeVar += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CSR -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo1 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CSR -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo2 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CSR -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.tipoSaida += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CSR -" << endl;
									ErroParte1 = true;
								}
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valCompAmp;
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ')')
									cont++;
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.frequencia;
								
								auxVariavel.valIni = 0;
								
								for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
								{
									if(ListaVariaveis[cont2].circuito == auxVariavel.circuito && ListaVariaveis[cont2].nomeVar == auxVariavel.nomeVar)
										componenteDeclarado = true;
								}
								
								if(componenteDeclarado == true)
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE COMPONENTES -" << endl;
									ErroParte1 = true;
								}
								else
								{
									ListaVariaveis.push_back(auxVariavel);
								}							
							}
							cont--;
						}
					}
					else if(auxString[cont] == 'P')
					{
						cont++;
						if(auxString[cont] == 'T')
						{
							cont++;
							if(auxString[cont] == ',')
							{
								Variaveis auxVariavel;
								auxVariavel.circuito = nomeCirc;
								auxVariavel.tipoComponente = "CPT";
								
								cont++;
								int iniCont = cont + 1;	
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
									
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CPT -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeVar += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CPT -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo1 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
									
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CPT -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo2 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
									
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE CPT -" << endl;
									ErroParte1 = true;
								}
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valCompAmp;
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ')')
									cont++;
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valIni;
								
								auxVariavel.frequencia = 0;
								auxVariavel.tipoSaida = "NONE";
								
								for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
								{
									if(ListaVariaveis[cont2].circuito == auxVariavel.circuito && ListaVariaveis[cont2].nomeVar == auxVariavel.nomeVar)
										componenteDeclarado = true;
								}
								
								if(componenteDeclarado == true)
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE COMPONENTES -" << endl;
									ErroParte1 = true;
								}
								else
								{
									ListaVariaveis.push_back(auxVariavel);
								}								
							}
						}
					}
				}
				else if(auxString[cont] == 'R')
				{
					cont ++;
					if(auxString[cont] == 'S')
					{
						cont++;
						if(auxString[cont] == 'T')
						{
							cont++;
							if(auxString[cont] == ',')
							{
								Variaveis auxVariavel;
								auxVariavel.circuito = nomeCirc;
								auxVariavel.tipoComponente = "RST";
								
								cont++;
								int iniCont = cont + 1;	
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
									
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE RST -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeVar += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE RST -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo1 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
									
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE RST -" << endl;
									ErroParte1 = true;
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo2 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ')')
									cont++;
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valCompAmp;
								
								auxVariavel.valIni = 0;
								auxVariavel.frequencia = 0;
								auxVariavel.tipoSaida = "NONE";
								
								for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
								{
									if(ListaVariaveis[cont2].circuito == auxVariavel.circuito && ListaVariaveis[cont2].nomeVar == auxVariavel.nomeVar)
										componenteDeclarado = true;
								}
								
								if(componenteDeclarado == true)
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE COMPONENTES -" << endl;
									ErroParte1 = true;
								}
								else
								{
									ListaVariaveis.push_back(auxVariavel);
								}							
							}
						}
					}
				}
				else if(auxString[cont] == 'I')
				{
					cont++;
					if(auxString[cont] == 'D')
					{
						cont++;
						if(auxString[cont] == 'T')
						{
							cont++;
							if(auxString[cont] == ',')
							{
								Variaveis auxVariavel;
								auxVariavel.circuito = nomeCirc;
								auxVariavel.tipoComponente = "IDT";
								
								cont++;
								int iniCont = cont + 1;	
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
									
								if(auxString[cont] == ')')
									{
										ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE IDT -" << endl;
										ErroParte1 = true;	
									}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeVar += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE IDT -" << endl;
									ErroParte1 = true;	
								}
																
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo1 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE IDT -" << endl;
									ErroParte1 = true;	
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo2 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE IDT -" << endl;
									ErroParte1 = true;	
								}
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valCompAmp;
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ')')
									cont++;
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valIni;
								
								auxVariavel.frequencia = 0;
								auxVariavel.tipoSaida = "NONE";
								
								for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
								{
									if(ListaVariaveis[cont2].circuito == auxVariavel.circuito && ListaVariaveis[cont2].nomeVar == auxVariavel.nomeVar)
										componenteDeclarado = true;
								}
								
								if(componenteDeclarado == true)
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE COMPONENTES -" << endl;
									ErroParte1 = true;
								}
								else
								{
									ListaVariaveis.push_back(auxVariavel);
								}							
							}
						}
					}
				}
				else if(auxString[cont] == 'V')
				{
					cont++;
					if(auxString[cont] == 'S')
					{
						cont++;
						if(auxString[cont] == 'R')
						{
							cont++;
							if(auxString[cont] == ',')
							{
								Variaveis auxVariavel;
								auxVariavel.circuito = nomeCirc;
								auxVariavel.tipoComponente = "VSR";
								
								cont++;
								int iniCont = cont + 1;	
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE VSR -" << endl;
									ErroParte1 = true;	
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeVar += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE VSR -" << endl;
									ErroParte1 = true;	
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo1 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE VSR -" << endl;
									ErroParte1 = true;	
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.nomeNo2 += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE VSR -" << endl;
									ErroParte1 = true;	
								}
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxVariavel.tipoSaida += auxString[cont2];
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ',' && auxString[cont] != ')')
									cont++;
								
								if(auxString[cont] == ')')
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE VSR -" << endl;
									ErroParte1 = true;	
								}
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.valCompAmp;
								
								cont++;
								iniCont = cont + 1;
								while(auxString[cont] != ')')
									cont++;
								
								auxNumString.clear();
								auxSS.str("");
								auxSS.clear();
								
								for(int cont2=iniCont; cont2 < cont; cont2++)
									auxNumString += auxString[cont2];
								
								auxSS << auxNumString;
								auxSS >> auxVariavel.frequencia;
								
								auxVariavel.valIni = 0;
								
								for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
								{
									if(ListaVariaveis[cont2].circuito == auxVariavel.circuito && ListaVariaveis[cont2].nomeVar == auxVariavel.nomeVar)
										componenteDeclarado = true;
								}
								
								if(componenteDeclarado == true)
								{
									ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DUPLICIDADE NA DECLARACAO DE COMPONENTES -" << endl;
									ErroParte1 = true;
								}
								else
								{
									ListaVariaveis.push_back(auxVariavel);
								}								
							}
						}
					}
				}
					if(componenteDeclarado == false)
						ArquivoTokens << "<CDECLARATION," << ListaVariaveis.size() - 1 << "> ";
			}
			else if(auxString[cont] == '[')
			{
				ArquivoTokens << "<[,> ";
			}
			else if(auxString[cont] == ']')
			{
				nomeCirc = "NONE";
				ArquivoTokens << "<],> ";
			}
		}
				
		//NUMEROS
		else if(auxString[cont] >= 48 && auxString[cont] <= 57)
		{
			int iniCont = cont;
			while((auxString[cont] >= 48 && auxString[cont] <= 57) || auxString[cont] == '.')
			{
				cont++;
			}
			ArquivoTokens << "<NUM,";
			for(int cont2 = iniCont; cont2 < cont; cont2++)
			{
				ArquivoTokens << auxString[cont2];
			}
			ArquivoTokens << "> ";
			cont--;
		}
		
		//VARIAVEIS
		else if(auxString[cont] >= 97 && auxString[cont] <= 122)
		{
			int iniCont = cont;
			string circNome, subCircNome, atribNome;
			while(auxString[cont] != '.')
			{
				cont++;
			}
			for(int cont2=iniCont; cont2 < cont; cont2++)
			{
				circNome += auxString[cont2];
			}
			
			cont++;
			iniCont = cont;
			while(auxString[cont] != '.' && auxString[cont] != ' ' && auxString[cont] != ',' && auxString[cont] != ')')
			{
				cont++;
			}
			for(int cont2=iniCont; cont2 < cont; cont2++)
			{
				subCircNome += auxString[cont2];
			}
			
			if(auxString[cont] == '.')
			{
				cont++;
				iniCont = cont;
				while(auxString[cont] != ' ' && auxString[cont] != ',' && auxString[cont] != ')')
				{
					cont++;
				}
				for(int cont2=iniCont; cont2 < cont; cont2++)
				{
					atribNome += auxString[cont2];
				}
				
				int cont2;
				bool erroaux = true;
				for(cont2 = 0; cont2 < Nos.size(); cont2++)
				{
					if(ListaVariaveis[cont2].circuito == circNome && ListaVariaveis[cont2].nomeVar == subCircNome)
					{
						ArquivoTokens << '<' << atribNome << "," << cont2 << "> ";
						erroaux = false;
						break;
					}
				}
				
				if(erroaux == true)
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: VARIAVEL INEXISTENTE -" << endl;
				
			}
			else
			{
				int cont2;
				for(cont2 = 0; cont2 < Nos.size(); cont2++)
				{
					if(Nos[cont2].circuito == circNome && Nos[cont2].nomeNo == subCircNome)
					{
						ArquivoTokens << "<NVAR," << cont2 << "> ";
						break;
					}
				}
				if(cont2 == Nos.size())
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: VARIAVEL INEXISTENTE -" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
		}
		
		//PALAVRAS RESERVADAS
		else if(auxString[cont] == 'C')
		{
			cont++;
			if(auxString[cont] == 'S')
			{
				cont++;
				if(auxString[cont] == 'R')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<CSR,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS CSR" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: CSR" << endl;
					ErroParte1 = true;
				}
			}
			else if(auxString[cont] == 'P')
			{
				cont++;
				if(auxString[cont] == 'T')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<CPT,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS CPT" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: CPT" << endl;
					ErroParte1 = true;
				}
			}
			else if(auxString[cont] == 'N')
			{
				cont++;
				if(auxString[cont] == 'T')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<CNT,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS CNT" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: CNT" << endl;
					ErroParte1 = true;
				}
			}
		}
		else if(auxString[cont] == 'R')
		{
			cont ++;
			if(auxString[cont] == 'S')
			{
				cont++;
				if(auxString[cont] == 'T')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<RST,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS RST" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: RST" << endl;
					ErroParte1 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: RST" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'I')
		{
			cont++;
			if(auxString[cont] == 'D')
			{
				cont++;
				if(auxString[cont] == 'T')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<IDT,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS IDT" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: IDT" << endl;
					ErroParte1 = true;
				}
				
			}
			else if(auxString[cont] == 'F')
			{
				cont++;
				if(auxString[cont] == '(')
				{
					ArquivoTokens << "<IF,> ";
					int iniExpr, endExpr;
					string expr;
					for(endExpr = auxString.length(); auxString[endExpr] != ')'; endExpr--)
					{}
					iniExpr = cont + 1;
								
					for(; iniExpr < endExpr; iniExpr++)
					{
						expr += auxString[iniExpr];
					}
								
					expressoes.push_back(expr);
					expressoesLinha.push_back(contLinha);
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA DE IF" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
		}
		else if(auxString[cont] == 'V')
		{
			cont++;
			if(auxString[cont] == 'S')
			{
				cont++;
				if(auxString[cont] == 'R')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<VSR,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS VSR" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: VSR" << endl;
					ErroParte1 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: VSR" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'S')
		{
			cont++;
			if(auxString[cont] == 'I')
			{
				cont++;
				if(auxString[cont] == 'N')
				{
					cont++;
					if(auxString[cont] == ';')
					{
						ArquivoTokens << "<SIN,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ; APOS SIN" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: SIN" << endl;
					ErroParte1 = true;
				}
			}
		}
		else if(auxString[cont] == 'O')
		{
			cont++;
			if(auxString[cont] == 'R')
			{
				cont++;
				if(auxString[cont] == ' ')
				{
					ArquivoTokens << "<OR,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS O OR" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: OR" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'L')
		{
			cont++;
			if(auxString[cont] == 'I')
			{
				cont++;
				if(auxString[cont] == 'S')
				{
					cont++;
					if(auxString[cont] == 'T')
					{
						cont++;
						if(auxString[cont] == '(')
						{
							ArquivoTokens << "<LIST,> ";
							int iniExpr, endExpr;
							string expr;
							for(iniExpr = cont; auxString[iniExpr] != ','; iniExpr++)
							{}
							for(endExpr = iniExpr + 1; auxString[endExpr] != ','; endExpr++)
							{}
								
							for(iniExpr += 2; iniExpr < endExpr; iniExpr++)
							{
								expr += auxString[iniExpr];
							}
								
							expressoes.push_back(expr);
							expressoesLinha.push_back(contLinha);
						}
						else
						{
							ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ( APOS LIST" << endl;
							ErroParte1 = true;
						}
						cont--;
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: LIST" << endl;
						ErroParte1 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: LIST" << endl;
					ErroParte1 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: LIST" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'P')
		{
			cont++;
			if(auxString[cont] == 'L')
			{
				cont++;
				if(auxString[cont] == 'O')
				{
					cont++;
					if(auxString[cont] == 'T')
					{
						cont++;
						if(auxString[cont] == '(')
						{
							ArquivoTokens << "<PLOT,> ";
							int iniExpr, endExpr;
							string expr;
							for(iniExpr = cont; auxString[iniExpr] != ','; iniExpr++)
							{}
							for(endExpr = iniExpr + 1; auxString[endExpr] != ','; endExpr++)
							{}
								
							for(iniExpr += 2; iniExpr < endExpr; iniExpr++)
							{
								expr += auxString[iniExpr];
							}
								
							expressoes.push_back(expr);
							expressoesLinha.push_back(contLinha);
						}
						else
						{
							ArquivoTokens << "ERRO ";
							ErroParte1 = true;
						}
						cont--;
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: PLOT" << endl;
						ErroParte1 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: PLOT" << endl;
					ErroParte1 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: PLOT" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'D')
		{
			cont++;
			if(auxString[cont] == 'O')
			{
				cont++;
				if(auxString[cont] == '(')
				{
					ArquivoTokens << "<DO,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ( APOS DO" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: DO" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'W')
		{
			cont++;
			if(auxString[cont] == 'H')
			{
				cont++;
				if(auxString[cont] == 'I')
				{
					cont++;
					if(auxString[cont] == 'L')
					{
						cont++;
						if(auxString[cont] == 'E')
						{
							cont++;
							if(auxString[cont] == '(')
							{
								ArquivoTokens << "<WHILE,> ";
								int iniExpr, endExpr;
								string expr;
								for(endExpr = auxString.length(); auxString[endExpr] != ')'; endExpr--)
								{}
								iniExpr = cont + 1;
								
								for(; iniExpr < endExpr; iniExpr++)
								{
									expr += auxString[iniExpr];
								}
								
								expressoes.push_back(expr);
								expressoesLinha.push_back(contLinha);
							}
							else
							{
								ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ( APOS WHILE" << endl;
								ErroParte1 = true;
							}
							cont--;
						}
						else
						{
							ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: WHILE" << endl;
							ErroParte1 = true;
						}
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: WHILE" << endl;
						ErroParte1 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: WHILE" << endl;
					ErroParte1 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: WHILE" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == 'A')
		{
			cont++;
			if(auxString[cont] == 'N')
			{
				cont++;
				if(auxString[cont] == 'D')
				{
					cont++;
					if(auxString[cont] == ' ')
					{
						ArquivoTokens << "<AND,> ";
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS AND" << endl;
						ErroParte1 = true;
					}
					cont--;
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: AND" << endl;
					ErroParte1 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: AND" << endl;
				ErroParte1 = true;
			}
		}
		else if(auxString[cont] == ':')
		{
			cont++;
			if(auxString[cont] == '=')
			{
				cont++;
				if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) )
				{
					ArquivoTokens << "<:=,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: FORMATACAO ERRADA NO :=" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
		}
		else if(auxString[cont] == '=')
		{
			cont++;
			if(auxString[cont] == '!')
			{
				cont++;
				if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
				{
					ArquivoTokens << "<!=,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS =!" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
			else if(auxString[cont] == '<')
			{
				cont++;
				if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
				{
					ArquivoTokens << "<<=,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS =<" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
			else if(auxString[cont] == '>')
			{
				cont++;
				if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
				{
					ArquivoTokens << "<>=,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS =>" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
			else if(auxString[cont] == '=')
			{
				cont++;
				if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
				{
					ArquivoTokens << "<==,> ";
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS ==" << endl;
					ErroParte1 = true;
				}
				cont--;
			}
		}
		else if(auxString[cont] == '+')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
					ArquivoTokens << "<+,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS +" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '-')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
					ArquivoTokens << "<-,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS -" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '/')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
					ArquivoTokens << "</,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS /" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '*')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
					ArquivoTokens << "<*,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS *" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '&')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
					ArquivoTokens << "<&,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS &" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '_')
		{
			cont++;
			if(auxString[cont] >= 97 && auxString[cont] <= 122)
			{
					ArquivoTokens << "<_,> ";
					int iniCont = cont;
					string circNome, subCircNome, atribNome;
					
					while(auxString[cont] != '.')
					{
						cont++;
					}
					for(int cont2=iniCont; cont2 < cont; cont2++)
					{
						circNome += auxString[cont2];
					}
						
					cont++;
					iniCont = cont;
					while(auxString[cont] != ')')
					{
						cont++;
					}
					for(int cont2=iniCont; cont2 < cont; cont2++)
					{
						subCircNome += auxString[cont2];
					}
					
					int cont2;
					
					for(cont2 = 0; cont2 < Nos.size(); cont2++)
					{
						if(ListaVariaveis[cont2].circuito == circNome && ListaVariaveis[cont2].nomeVar == subCircNome)
						{
							ArquivoTokens << "<NCMP," << cont2 << "> ";
							break;
						}
					}
					if(cont2 == Nos.size())
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: VARIAVEL INEXISTENTE -" << endl;
						ErroParte1 = true;
					}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE UMA VARIAVEL APOS _" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '#')
		{
			cont++;
			if(auxString[cont] >= 97 && auxString[cont] <= 122)
			{
					ArquivoTokens << "<#,> ";
					int iniCont = cont;
					string circNome, subCircNome, atribNome;
					while(auxString[cont] != '.')
					{
						cont++;
					}
					for(int cont2=iniCont; cont2 < cont; cont2++)
					{
						circNome += auxString[cont2];
					}
			
					cont++;
					iniCont = cont;
					while(auxString[cont] != ')')
					{
						cont++;
					}
					for(int cont2=iniCont; cont2 < cont; cont2++)
					{
						subCircNome += auxString[cont2];
					}
					
					int cont2;
					
					for(cont2 = 0; cont2 < Nos.size(); cont2++)
					{
						if(ListaVariaveis[cont2].circuito == circNome && ListaVariaveis[cont2].nomeVar == subCircNome)
						{
							ArquivoTokens << "<NCMP," << cont2 << "> ";
							break;
						}
					}
					if(cont2 == Nos.size())
					{
						ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: VARIAVEL INEXISTENTE -" << endl;
						ErroParte1 = true;
					}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE UMA VARIAVEL #" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '>')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
				ArquivoTokens << "<>,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS >" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '<')
		{
			cont++;
			if(auxString[cont] == ' ' || (auxString[cont] >= 48 && auxString[cont] <= 57) || (auxString[cont] >= 97 && auxString[cont] <= 122))
			{
				ArquivoTokens << "<<,> ";
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << contLinha << " -SUGESTÃO: ESPERA-SE ESPACO APOS <" << endl;
				ErroParte1 = true;
			}
			cont--;
		}
		else if(auxString[cont] == '(')
		{
			ArquivoTokens << "<(,> ";
		}
		else if(auxString[cont] == ')')
		{
			ArquivoTokens << "<),> ";
		}
		else if(auxString[cont] == '[')
		{
			ArquivoTokens << "<[,> ";
		}
		else if(auxString[cont] == ']')
		{
			ArquivoTokens << "<],> ";
		}
		else if(auxString[cont] == ',')
		{
			ArquivoTokens << "<,,> ";
		}
		else if(auxString[cont] == ';')
		{	
			ArquivoTokens << "<;,> ";
		}
		else if(auxString[cont] == '"')
		{
			cont++;
			int iniCont = cont;
			while(auxString[cont] != '"')
			{
				cont++;
			}
			ArquivoTokens << "<STRING,";
			for(int cont2 = iniCont; cont2 < cont; cont2++)
			{
				ArquivoTokens << auxString[cont2];
			}
			ArquivoTokens << "> ";
			
		}
		else
		{
			
		}
		
	}
	ArquivoTokens << endl;
}

//Analise Sintatica
ArquivoTokens.close();
ifstream ArquivoTokensSin(nomeArquivoTokens.c_str());
vector <StringArm> TabelaSin;


//Construcao da tabela com tokens
while(!ArquivoTokensSin.eof() && ErroParte1 != true)
{
	getline(ArquivoTokensSin, auxString);
	StringArm StringArmAux;
	int cont;
	for(cont = 0; cont < auxString.length(); cont++)
	{
		int iniCont = cont;
		
		while(auxString[cont] != ' ')
			cont++;
			
		string StringAux2;
		for(int cont2=iniCont; cont2 < cont; cont2++)
			StringAux2 += auxString[cont2];
			
		StringArmAux.listaStrings.push_back(StringAux2);
	}
	
	string StringAux2 = "\n";
	StringArmAux.listaStrings.push_back(StringAux2);
	TabelaSin.push_back(StringArmAux);
}

declaracao = false;
bool execucao = false;
int contEscopo = 0, linhaEscopo = -1;
int contBlocoFnc = 0, linhaBloco = -1;

for(int cont = 0; cont < TabelaSin.size(); cont++)
{
	for(int cont2 = 0; cont2 < TabelaSin[cont].listaStrings.size(); cont2++)
	{
		if(TabelaSin[cont].listaStrings[cont2] == "<CIRCDEF,>")
		{
			if(execucao == true)
			{
				ArquivoErros << "BLOCO CIRCDEF E OUTDEF INVERTIDOS" << endl;
				ErroParte2 = true;
			}
			else
			{
				declaracao = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<DECLARATION,>" && declaracao == true)
		{
			if(TabelaSin[cont].listaStrings[cont2 + 1] == "<[,>" || TabelaSin[cont + 1].listaStrings[0] == "<[,>")
			{
				contEscopo++;
				linhaEscopo = cont;
				if(TabelaSin[cont].listaStrings[cont2 + 1] == "<[,>")
				{
					cont++;
					cont2 = 0;
				}
				else
				{
					cont += 2;
					cont2 = 0;
				}
				
				if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 2] != "<;,>")
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: FALTA DE ; APOS DECLARACAO DOS NOS DO CIRCUITO" << endl;
					ErroParte2 = true;
				}
				
				if(TabelaSin[cont].listaStrings[cont2].find("<NDECLARATION,") == -1)
				{
					cout << TabelaSin[cont].listaStrings[cont2] << endl;
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE DECLARACAO DE NO" << endl;
					ErroParte2 = true;
				}
				cont2++;
				while(TabelaSin[cont].listaStrings[cont2] != "<;,>")
				{
					if(TabelaSin[cont].listaStrings[cont2] != "<,,>")
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , SEPARANDO OS NOS" << endl;
						ErroParte2 = true;
					}
					if(TabelaSin[cont].listaStrings[cont2 + 1].find("<NDECLARATION,") == -1)
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE DECLARACAO DE NO" << endl;
						ErroParte2 = true;
					}
					cont2 += 2;
				}
				
				cont++;
				cont2 = 0;
				
				if(TabelaSin[cont].listaStrings[cont2].find("<CDECLARATION,") == -1)
				{
					cout << TabelaSin[cont].listaStrings[cont2] << endl;
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE DECLARACAO DE COMPONENTE" << endl;
					ErroParte2 = true;
				}
				cont2++;
				while(TabelaSin[cont].listaStrings[cont2] != "<;,>")
				{
					if(TabelaSin[cont].listaStrings[cont2] != "<,,>")
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , SEPARANDO OS NOS" << endl;
						ErroParte2 = true;
					}
					if(TabelaSin[cont].listaStrings[cont2 + 1].find("<CDECLARATION,") == -1)
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE DECLARACAO DE COMPONENTE" << endl;
						ErroParte2 = true;
					}
					cont2 += 2;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: FALTA DE [ APOS NOME DO CIRCUITO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<OUTDEF,>")
		{
			execucao = true;
			declaracao = false;
			if(TabelaSin[cont].listaStrings[cont2 + 1] == "<[,>")
			{
				contEscopo++;
				linhaEscopo = cont;
			}
			else if(TabelaSin[cont].listaStrings[cont2 + 1] != "\n")
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: FORMATACAO ERRADA DO OUTDEF" << endl;
				ErroParte2 = true;
			}
			else if(TabelaSin[cont + 1].listaStrings[0] == "<[,>")
			{
				contEscopo++;
				linhaEscopo = cont + 1;
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DA ABERTURA DE ESCOPO DO OUTDEF" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<WHILE,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 + 1] == "<(,>")
			{
				contBlocoFnc++;
				linhaBloco = cont;
				if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 1] == "<[,>" || TabelaSin[cont + 1].listaStrings[0] == "<[,>")
				{
					if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 1] == "<[,>")
					{
						contEscopo++;
						linhaEscopo = cont;
					}
					if(TabelaSin[cont + 1].listaStrings[0] == "<[,>")
					{
						contEscopo++;
						linhaEscopo = cont + 1;
					}
					
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DA ABERTURA DE ESCOPO DE WHILE" << endl;
					ErroParte2 = true;
				}
				cont2++;
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: FORMATACAO ERRADA DE WHILE" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<DO,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 + 1] == "<(,>")
			{
				contBlocoFnc++;
				linhaBloco = cont;
				if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 1] == "<[,>" || TabelaSin[cont + 1].listaStrings[0] == "<[,>")
				{
					if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 1] == "<[,>")
					{
						contEscopo++;
						linhaEscopo = cont;
					}
					if(TabelaSin[cont + 1].listaStrings[0] == "<[,>")
					{
						contEscopo++;
						linhaEscopo = cont + 1;
					}
					
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DA ABERTURA DE ESCOPO DE DO" << endl;
					ErroParte2 = true;
				}
				cont2++;
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: FORMATACAO ERRADA DE DO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<IF,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 + 1] == "<(,>")
			{
				contBlocoFnc++;
				linhaBloco = cont;
				if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 1] == "<[,>" || TabelaSin[cont + 1].listaStrings[0] == "<[,>")
				{
					if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 1] == "<[,>")
					{
						contEscopo++;
						linhaEscopo = cont;
					}
					if(TabelaSin[cont + 1].listaStrings[0] == "<[,>")
					{
						contEscopo++;
						linhaEscopo = cont + 1;
					}
					
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DA ABERTURA DE ESCOPO DE IF" << endl;
					ErroParte2 = true;
				}
				cont2++;
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: FORMATACAO ERRADA DE IF" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<+,>" || TabelaSin[cont].listaStrings[cont2] == "<-,>" || TabelaSin[cont].listaStrings[cont2] == "<*,>" || TabelaSin[cont].listaStrings[cont2] == "</,>" || TabelaSin[cont].listaStrings[cont2] == "<AND,>" || TabelaSin[cont].listaStrings[cont2] == "<OR,>" || TabelaSin[cont].listaStrings[cont2] == "<<,>" || TabelaSin[cont].listaStrings[cont2] == "<>,>" || TabelaSin[cont].listaStrings[cont2] == "<>=,>" || TabelaSin[cont].listaStrings[cont2] == "<<=,>" || TabelaSin[cont].listaStrings[cont2] == "<==,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 - 1] == "<),>" && TabelaSin[cont].listaStrings[cont2 + 1] == "<(,>")
			{}
			else if(TabelaSin[cont].listaStrings[cont2] == "<+,>" || TabelaSin[cont].listaStrings[cont2] == "<-,>" || TabelaSin[cont].listaStrings[cont2] == "<*,>" || TabelaSin[cont].listaStrings[cont2] == "</,>")
			{
				if(TabelaSin[cont].listaStrings[cont2 - 1].find("<NUM,") != -1 && TabelaSin[cont].listaStrings[cont2 + 1].find("<NUM,") != -1)
				{}
				else if(TabelaSin[cont].listaStrings[cont2 - 1] == "<),>" && TabelaSin[cont].listaStrings[cont2 + 1].find("<NUM,") != -1)
				{}
				else if(TabelaSin[cont].listaStrings[cont2 - 1].find("<NUM,") != -1 && TabelaSin[cont].listaStrings[cont2 + 1] == "<(,>")
				{}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: ESPERA-SE UM TIPO NUMERO OU ABERTURA DE ESCOPO EM TORNO DO OPERADOR" << endl;
					ErroParte2 = true;
				}
			}
			else if(TabelaSin[cont].listaStrings[cont2] == "<<,>" || TabelaSin[cont].listaStrings[cont2] == "<>,>" || TabelaSin[cont].listaStrings[cont2] == "<>=,>" || TabelaSin[cont].listaStrings[cont2] == "<<=,>" || TabelaSin[cont].listaStrings[cont2] == "<==,>")
			{
				if(TabelaSin[cont].listaStrings[cont2 - 1].find("<NUM,") != -1 && TabelaSin[cont].listaStrings[cont2 + 1].find("<NUM,") != -1)
				{}
				else if(TabelaSin[cont].listaStrings[cont2 - 1] == "<),>" && TabelaSin[cont].listaStrings[cont2 + 1].find("<NUM,") != -1)
				{}
				else if(TabelaSin[cont].listaStrings[cont2 - 1].find("<NUM,") != -1 && TabelaSin[cont].listaStrings[cont2 + 1] == "<(,>")
				{}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: ESPERA-SE UM TIPO NUMERO OU ABERTURA DE ESCOPO EM TORNO DO OPERADOR DE COMPARACAO" << endl;
					ErroParte2 = true;
				}
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<&,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 - 1].find("<NVAR,") != -1 && TabelaSin[cont].listaStrings[cont2 + 1].find("<NVAR,") != -1 && TabelaSin[cont].listaStrings[cont2 - 2] == "<(,>" && TabelaSin[cont].listaStrings[cont2 + 2] == "<),>")
			{}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: ESPERA-SE O TIPO NO EM TORNO DO OPERADOR DE TENSAO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<#,>" || TabelaSin[cont].listaStrings[cont2] == "<_,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 + 1].find("<NCMP,") != -1 && TabelaSin[cont].listaStrings[cont2 + 2] == "<),>" && TabelaSin[cont].listaStrings[cont2 - 1] == "<(,>")
			{}
			else
			{
				if(TabelaSin[cont].listaStrings[cont2] == "<#,>")
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: ESPERA-SE O TIPO COMPONENTE APOS O OPERADOR DE POTENCIA" << endl;
					ErroParte2 = true;
				}
				else if(TabelaSin[cont].listaStrings[cont2] == "<_,>")
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: ESPERA-SE O TIPO COMPONENTE APOS O OPERADOR DE CORRENTE" << endl;
					ErroParte2 = true;
				}
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<;,>" || TabelaSin[cont].listaStrings[cont2] == "<[,>")
		{
			if(contBlocoFnc != 0)
			{
				ArquivoErros << "ERRO NA LINHA " << linhaEscopo << " -SUGESTÃO: ESCOPO NAO BALANCEADO" << endl;
				contBlocoFnc = 0;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<(,>")
		{
			contBlocoFnc++;
			linhaBloco = cont;
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<),>")
		{
			contBlocoFnc--;
			linhaBloco = cont;
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<],>")
		{
			contEscopo--;
			linhaEscopo = cont;
		}
		else if(TabelaSin[cont].listaStrings[cont2].find("<CTYPE,") != -1)
		{
			cont2++;
			if(TabelaSin[cont].listaStrings[cont2] == "<:=,>")
			{
				cont2++;
				if(TabelaSin[cont].listaStrings[cont2] == "<CPT,>" || TabelaSin[cont].listaStrings[cont2] == "<IDT,>" || TabelaSin[cont].listaStrings[cont2] == "<RST,>" || TabelaSin[cont].listaStrings[cont2] == "<VSR,>" || TabelaSin[cont].listaStrings[cont2] == "<CSR,>")
				{
					cont2++;
					if(TabelaSin[cont].listaStrings[cont2] == "<;,>")
					{}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE ; APOS ATRIBUICAO" << endl;
						ErroParte2 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE COMPONENTE INEXISTENTE" << endl;
					ErroParte2 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: VARIAVEL FORA DE CONTEXTO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2].find("<OTYPE,") != -1)
		{
			cont2++;
			if(TabelaSin[cont].listaStrings[cont2] == "<:=,>")
			{
				cont2++;
				if(TabelaSin[cont].listaStrings[cont2] == "<SIN,>" || TabelaSin[cont].listaStrings[cont2] == "<CNT,>")
				{
					cont2++;
					if(TabelaSin[cont].listaStrings[cont2] == "<;,>")
					{}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE ; APOS ATRIBUICAO" << endl;
						ErroParte2 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE SAIDA INEXISTENTE" << endl;
					ErroParte2 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: VARIAVEL FORA DE CONTEXTO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2].find("<NNAMEA,") != -1 || TabelaSin[cont].listaStrings[cont2].find("<NNAMEB,") != -1)
		{
			cont2++;
			if(TabelaSin[cont].listaStrings[cont2] == "<:=,>")
			{
				cont2++;
				if(TabelaSin[cont].listaStrings[cont2].find("<STRING,") != -1)
				{
					cont2++;
					if(TabelaSin[cont].listaStrings[cont2] == "<;,>")
					{}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE ; APOS ATRIBUICAO" << endl;
						ErroParte2 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE STRING OBRIGATORIO ATRIBUICAO" << endl;
					ErroParte2 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: VARIAVEL FORA DE CONTEXTO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2].find("<AMPLITUDE,") != -1 || TabelaSin[cont].listaStrings[cont2].find("<IVALUE,") != -1 || TabelaSin[cont].listaStrings[cont2].find("<FREQUENCY,") != -1)
		{
			cont2++;
			if(TabelaSin[cont].listaStrings[cont2] == "<:=,>")
			{
				cont2++;
				if(TabelaSin[cont].listaStrings[cont2].find("<NUM,") != -1)
				{
					cont2++;
					if(TabelaSin[cont].listaStrings[cont2] == "<;,>")
					{}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE ; APOS ATRIBUICAO" << endl;
						ErroParte2 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO ATRIBUICAO" << endl;
					ErroParte2 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: VARIAVEL FORA DE CONTEXTO" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<LIST,>")
		{
			if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 2] == "<;,>")
			{
				if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 4].find("<NUM,") != -1)
				{
					if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 5] == "<,,>")
					{
						if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 6].find("<NUM,") != -1)
						{
							if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 7] == "<,,>")
							{
								if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 8].find("<NUM,") != -1)
								{
									if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 9] == "<,,>")
									{}
									else
									{
										ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , ENTRE INTERVALO E SAIDA" << endl;
										ErroParte2 = true;
									}
								}
								else
								{
									ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO NO INTERVALO" << endl;
									ErroParte2 = true;
								}
							}
							else
							{
								ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , ENTRE TEMPO INICIAL E INTERVALO" << endl;
								ErroParte2 = true;
							}
						}
						else
						{
							ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO NO TEMPO INICIAL" << endl;
							ErroParte2 = true;
						}
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , ENTRE TEMPO FINAL E INICIAL" << endl;
						ErroParte2 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO NO TEMPO FINAL" << endl;
					ErroParte2 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE ; NO FINAL DA LINHA" << endl;
				ErroParte2 = true;
			}
		}
		else if(TabelaSin[cont].listaStrings[cont2] == "<PLOT,>")
		{
			if(TabelaSin[cont].listaStrings[cont2 + 2].find("<STRING,") != -1)
			{
				if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 2] == "<;,>")
				{
					if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 4].find("<NUM,") != -1)
					{
						if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 5] == "<,,>")
						{
							if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 6].find("<NUM,") != -1)
							{
								if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 7] == "<,,>")
								{
									if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 8].find("<NUM,") != -1)
									{
										if(TabelaSin[cont].listaStrings[TabelaSin[cont].listaStrings.size() - 9] == "<,,>")
										{}
										else
										{
											ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , ENTRE INTERVALO E SAIDA" << endl;
											ErroParte2 = true;
										}
									}
									else
									{
										ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO NO INTERVALO" << endl;
										ErroParte2 = true;
									}
								}
								else
								{
									ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , ENTRE TEMPO INICIAL E INTERVALO" << endl;
									ErroParte2 = true;
								}
							}
							else
							{
								ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO NO TEMPO INICIAL" << endl;
								ErroParte2 = true;
							}
						}
						else
						{
							ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE , ENTRE TEMPO FINAL E INICIAL" << endl;
							ErroParte2 = true;
						}
					}
					else
					{
						ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: TIPO DE NUMERICO OBRIGATORIO NO TEMPO FINAL" << endl;
						ErroParte2 = true;
					}
				}
				else
				{
					ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: AUSENCIA DE ; NO FINAL DA LINHA" << endl;
					ErroParte2 = true;
				}
			}
			else
			{
				ArquivoErros << "ERRO NA LINHA " << cont << " -SUGESTÃO: NOME DE ARQUIVO DE SAIDA DEVE SER UMA STRING" << endl;
				ErroParte2 = true;
			}
		}
	}
}

if(contEscopo != 0)
{
	ArquivoErros << "ERRO NA LINHA " << contEscopo << " -SUGESTÃO: ESCOPO DESBALANCEADO" << endl;
	ErroParte2 = true;
}

vector <MatrizSaida> Saida;

if(ErroParte1 == false && ErroParte2 == false)
{
	int contIni = 0, contFim = 0;
	MatrizSaida matrizAux;	
	for(int cont1 = 0; cont1 < Nos.size(); cont1++)
	{
		if(encontraCircuitoMatriz(Saida, Nos[cont1].circuito) == -1)
		{
			matrizAux.circuito = Nos[cont1].circuito;
			Saida.push_back(matrizAux);
		}
	}
	for(int cont1 = 0; cont1 < Nos.size(); cont1++)
	{
		Saida[encontraCircuitoMatriz(Saida, Nos[cont1].circuito)].nos.push_back(Nos[cont1].nomeNo);
	}
	for(int cont1 = 0; cont1 < Saida.size(); cont1++)
	{
		Saida[cont1].matrizSaida = new string*[Saida[cont1].nos.size()];
		for(int cont2 = 0; cont2 < Saida[cont1].nos.size(); cont2++)
		{
			Saida[cont1].matrizSaida[cont2] = new string[Saida[cont1].nos.size()];
		}
	}
	for(int cont1 = 0; cont1 < ListaVariaveis.size(); cont1++)
	{
		if(ListaVariaveis[cont1].tipoComponente == "RST")
		{
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ (";
			auxSS.str("");
			auxSS.clear();
			auxSS << ListaVariaveis[cont1].valCompAmp;
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " * (V";
			
			auxSS.str("");
			auxSS.clear();
			auxSS << encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1);
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();

			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ",";

			auxSS.str("");
			auxSS.clear();
			auxSS << encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2);
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
		
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ")) ";
		}
		else if(ListaVariaveis[cont1].tipoComponente == "CPT")
		{
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ ((";
			
			auxSS.str("");
			auxSS.clear();
			auxSS << ListaVariaveis[cont1].valCompAmp * ListaVariaveis[cont1].valIni;
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ") + (";
			
			auxSS.str("");
			auxSS.clear();
			auxSS << ListaVariaveis[cont1].valCompAmp;
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " + (s * ";

			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "(V";
						
			auxSS.str("");
			auxSS.clear();
			auxSS << encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1);
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();

			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ",";

			auxSS.str("");
			auxSS.clear();
			auxSS << encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2);
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();

			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ")))) ";

		}
		else if(ListaVariaveis[cont1].tipoComponente == "IDT")
		{
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ ((";
			
			auxSS.str("");
			auxSS.clear();
			auxSS << ListaVariaveis[cont1].valIni;
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " / s) + ((V";

			auxSS.str("");
			auxSS.clear();
			auxSS << encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1);
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();

			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ",";

			auxSS.str("");
			auxSS.clear();
			auxSS << encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2);
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();

			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += ") / (";

			auxSS.str("");
			auxSS.clear();
			auxSS << ListaVariaveis[cont1].valCompAmp;
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
			Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " * s)))";

		}
		else if(ListaVariaveis[cont1].tipoComponente == "CSR")
		{
			if(ListaVariaveis[cont1].tipoSaida == "CNT")
			{
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ (";
				
				auxSS.str("");
				auxSS.clear();
				auxSS << ListaVariaveis[cont1].valCompAmp;
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " / s)";
			}
			else if(ListaVariaveis[cont1].tipoSaida == "SIN")
			{
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ (";

				auxSS.str("");
				auxSS.clear();
				auxSS << ListaVariaveis[cont1].frequencia;
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " / (";

				auxSS.str("");
				auxSS.clear();
				auxSS << ListaVariaveis[cont1].frequencia * ListaVariaveis[cont1].frequencia;
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " + (s * s)))";
			}
		}
		else if(ListaVariaveis[cont1].tipoComponente == "VSR")
		{
			if(ListaVariaveis[cont1].tipoSaida == "CNT")
			{
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ VOLTAGE(";
				
				auxSS.str("");
				auxSS.clear();
				auxSS << ListaVariaveis[cont1].valCompAmp;
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " / s)";
			}
			else if(ListaVariaveis[cont1].tipoSaida == "SIN")
			{
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += "+ VOLTAGE(";

				auxSS.str("");
				auxSS.clear();
				auxSS << ListaVariaveis[cont1].frequencia;
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " / (";

				auxSS.str("");
				auxSS.clear();
				auxSS << ListaVariaveis[cont1].frequencia * ListaVariaveis[cont1].frequencia;
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida,ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += auxSS.str();
			
				Saida[encontraCircuitoMatriz(Saida, ListaVariaveis[cont1].circuito)].matrizSaida[encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo1)][encontraNoMatriz(Saida, ListaVariaveis[cont1].circuito, ListaVariaveis[cont1].nomeNo2)] += " + (s * s)))";
			}
		}
	}
	for(int cont1 = 0; cont1 < Saida.size(); cont1++)
	{
		ArquivoIntermediario << "#" << Saida[cont1].circuito << endl;
		for(int cont2 = 0; cont2 < Saida[cont1].nos.size(); cont2++)
		{
			ArquivoIntermediario << '<' << Saida[cont1].nos[cont2] << endl;
		}

		for(int cont2 = 0; cont2 < ListaVariaveis.size(); cont2++)
		{
			if(Saida[cont1].circuito == ListaVariaveis[cont2].circuito)
			{
				/*string circuito;
		string nomeVar, tipoComponente, tipoSaida, nomeNo1, nomeNo2;
		float valCompAmp, valIni, frequencia; */
				ArquivoIntermediario << '>' << ListaVariaveis[cont2].nomeVar << '\t' << ListaVariaveis[cont2].tipoComponente << '\t' << ListaVariaveis[cont2].nomeNo1 << '\t' << ListaVariaveis[cont2].nomeNo2 << '\t' << ListaVariaveis[cont2].tipoSaida << '\t' << ListaVariaveis[cont2].valCompAmp << '\t' << ListaVariaveis[cont2].frequencia << '\t' << ListaVariaveis[cont2].valIni << '\t' << endl;
			}
		}

		ArquivoIntermediario << '@' << endl;
		
		for(int cont3 = 0; cont3 < Saida[cont1].nos.size(); cont3++)
		{
			for(int cont4 = 0; cont4 < Saida[cont1].nos.size(); cont4++)
			{
				if(Saida[cont1].matrizSaida[cont3][cont4] == "")
				{
					ArquivoIntermediario <<"\t\t\t\t" << "+ 0";
				}
				else
				{
					ArquivoIntermediario <<"\t\t\t\t" << Saida[cont1].matrizSaida[cont3][cont4];
				}
			}
			ArquivoIntermediario << endl;
		}
		ArquivoIntermediario << endl;
	}
	
	CodigoFonte.close();
	ifstream CodigoFonte(nomeArquivoFonte.c_str());
	bool controle = false;
	while(!CodigoFonte.eof())
	{
		getline(CodigoFonte, auxString);
		if(auxString == "OUTDEF")
		{
			controle = true;
		}
		else if(auxString == "OUTDEF[")
		{
			controle = true;
			ArquivoIntermediarioExecucao << "[" << endl;
		}
		else if(controle == true)
		{
			ArquivoIntermediarioExecucao << auxString << endl;
		}
	}
}

remove("CodigoIntermediarioExpressoes.txt");
ArquivoErros.close();

for(int cont = 0; cont < expressoes.size(); cont++)
{
	ArvoreExpr AuxArvore;
	SeparaExpr(&AuxArvore, expressoes[cont], expressoesLinha[cont]);
	ofstream ArquivoIntermediarioExpressao("CodigoIntermediarioExpressoes.txt", ios::app);
	ArquivoIntermediarioExpressao << expressoes[cont] << endl;
	ArquivoIntermediarioExpressao.close();
	arquivoExpressoes(0, &AuxArvore, "CodigoIntermediarioExpressoes.txt");
	ArquivoIntermediarioExpressao.open("CodigoIntermediarioExpressoes.txt", ios::app);
	ArquivoIntermediarioExpressao << endl << endl;
	ArquivoIntermediarioExpressao.close();
}

	CodigoFonte.close();
	ArquivoPalavrasReservadas.close();
	ArquivoTokens.close();
	ArquivoIntermediario.close();
	ArquivoIntermediarioExecucao.close();

return 0;
}

