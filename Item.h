# ifndef ITEM_H
# define ITEM_H

enum class Qualidade {PESSIMA, OTIMA};

class Item{
	
	public:
		
		Item();
		Item(string, float, Qualidade, bool, int);
		
		void setNome(string);
		void setQualidade(Qualidade);
		void setPreco(float);
		void setFoiEmbalado(bool);
		void setId(int);
		
		string getNome();
		Qualidade getQualidade();
		float getPreco();
		int getId();
		
		bool getFoiEmbalado();
		bool prontoParaEnvio();
	
	private:
		string nome;
		Qualidade qualidade;
		float preco;	
		bool foiEmbalado;
		int id;
};


# endif
