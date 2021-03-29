package Model;

import java.util.List;

public interface ICatProd {

    /**
     * Função que testa se existe ou não um produto.
     * @param c String com o código do produto a testar.
     * @return Retorna True caso o produto exista e False caso não exista.
     */
    boolean existe(String c);

    /**
     * Função que determina o número de produtos.
     * @return Retorna o tamanho do map.
     */
    int size();

    /**
     * Função que insere todos os produtos numa lista.
     * @return Retorna a lista com todos os produtos.
     */
    List<Produto> prodList();
}
