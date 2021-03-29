package Model;

import java.io.Serializable;

/**
 * Classe que contém o código de um produto.
 */
public class Produto implements IProduto, Serializable {
    private String id;

    /**
     * Construtor da Classe Produto.
     * @param id String com o código de um produto.
     */
    public Produto(String id){
        this.id = id;
    }

    /**
     *@return Retorna uma String correspondente ao código do produto.
     */
    public String getId() {
        return id;
    }

    /**
     * Função que testa se um produto é válido ou não.
     * @return Retorna True caso o produto seja válido e False caso não seja.
     */
    public boolean isValido(){
        return this.id.matches("[A-Z]{2}([1-9]\\d{3})");
    }

    /**
     * Função que clona um produto.
     * @return Retorna o clone do produto.
     */
    public Produto clone(){
        return new Produto(this.getId());
    }
}
