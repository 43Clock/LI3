package Model;

public interface ICliente {

    /**
     *@return Retorna uma String correspondente ao código do cliente.
     */
    String getId();

    /**
     * Função que testa se um cliente é válido ou não.
     * @return Retorna True caso o cliente seja válido e False caso não seja.
     */
    boolean isValido();

    /**
     * Função que clona um cliente.
     * @return Retorna o clone do cliente.
     */
    ICliente clone();
}
