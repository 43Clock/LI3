package Model;

public interface ICatCli {

    /**
     * Função que testa se existe ou não um cliente.
     * @param c String com o código do cliente a testar.
     * @return Retorna True caso o cliente exista e False caso não exita.
     */
    boolean existe(String c);

    /**
     * Função que determina o número de clientes.
     * @return Retorna o tamanho do map.
     */
    int size();
}
