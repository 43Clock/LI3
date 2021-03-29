package Model;

import java.io.IOException;
import java.io.Serializable;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

/**
 * Classe que contém um map com todos os produtos.
 */

public class CatProd implements ICatProd, Serializable {
    private Map<String,Produto> lista;

    /**
     * Construtor da Classe CatProd.
     * @param fp String com a path do ficheiro de onde vamos ler os produtos.
     * @throws IOException Exceção para o caso das paths nao ser válida.
     */
    public CatProd(String fp) throws IOException {
        List<String> produtos = Files.readAllLines(Paths.get(fp), Charset.defaultCharset());
        this.lista = produtos.stream().map(Produto::new)
                .filter(Produto::isValido)
                .collect(Collectors
                        .toMap(Produto::getId, Function.identity(),(a,b)->a, HashMap::new));
    }

    /**
     * Função que testa se existe ou não um produto.
     * @param c String com o código do produto a testar.
     * @return Retorna True caso o produto exista e False caso não exista.
     */
    public boolean existe(String c){
        return this.lista.containsKey(c);
    }

    /**
     * Função que determina o número de produtos.
     * @return Retorna o tamanho do map.
     */
    public int size(){
        return this.lista.size();
    }

    /**
     * Função que insere todos os produtos numa lista.
     * @return Retorna a lista com todos os produtos.
     */
    public List<Produto> prodList(){
        return new ArrayList<>(this.lista.values());
    }
}
