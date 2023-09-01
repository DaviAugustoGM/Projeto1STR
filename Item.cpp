# include "Item.h"

Item::Item(){
	this->nome = "";
	this->preco = 0.0;
	this->qualidade = Qualidade::PESSIMA;
	this->foiEmbalado = false;	
}

Item::Item(string nome, float preco, Qualidade qualidade, bool embalado, int id){
	setNome(nome);
	setPreco(preco);
	setQualidade(qualidade);
	setFoiEmbalado(embalado);
	setId(id);
}

void Item::setNome(string nome){
	this->nome = nome;
}

void Item::setQualidade(Qualidade qualidade){
	this->qualidade = qualidade;
}

void Item::setPreco(float preco){
	this->preco = preco;
}

void Item::setFoiEmbalado(bool foiEmbalado){
	this->foiEmbalado = foiEmbalado;
}

void Item::setId(int id){
	this->id = id;
}
		
string Item::getNome(){
	return nome;
}

Qualidade Item::getQualidade(){
	return qualidade;
}

float Item::getPreco(){
	return preco;
}
		
bool Item::getFoiEmbalado(){
	return foiEmbalado;	
}

int Item::getId(){
	return id;
}


bool Item::prontoParaEnvio(){
	
	if(qualidade == Qualidade::OTIMA && foiEmbalado)
		return true;
	
	return false;
}
