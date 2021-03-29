package Model;

public interface IProduto {

    /**
     *@return Retorna uma String correspondente ao código do produto.
     */
    String getId();

    /**
     * Função que testa se um produto é válido ou não.
     * @return Retorna True caso o produto seja válido e False caso não seja.
     */
    boolean isValido();

    /**
     * Função que clona um produto.
     * @return Retorna o clone do produto.
     */
    IProduto clone();
}
