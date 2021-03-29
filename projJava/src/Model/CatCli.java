package Model;

import java.io.IOException;
import java.io.Serializable;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.function.Function;
import java.util.stream.Collectors;

/**
 * Classe que contém um map com todos os clientes.
 */
public class CatCli implements  ICatCli, Serializable {
    private Map<String,Cliente> lista;

    /**
     * Construtor da Classe CatCli.
     * @param fp String com a path do ficheiro de onde vamos ler os clientes.
     * @throws IOException Exceção para o caso das paths nao ser válida.
     */
    public CatCli(String fp) throws IOException {
        List<String> clientes = Files.readAllLines(Paths.get(fp), Charset.defaultCharset());
        this.lista = clientes.stream().map(Cliente::new)
                                      .filter(Cliente::isValido)
                                      .collect(Collectors
                                              .toMap(Cliente::getId, Function.identity(),(a,b)->a, HashMap::new));
    }

    /**
     * Função que testa se existe ou não um cliente.
     * @param c String com o código do cliente a testar.
     * @return Retorna True caso o cliente exista e False caso não exita.
     */
    public boolean existe(String c){
        return this.lista.containsKey(c);
    }

    /**
     * Função que determina o número de clientes.
     * @return Retorna o tamanho do map.
     */
    public int size(){
        return this.lista.size();
    }
}
