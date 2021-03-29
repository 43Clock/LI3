package Model;

import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import Exceptions.*;


/**
 * Classe que contem todas as estruturas necessarias à resposta das queries propostas, sendo este o modulo principal
 * onde são feitos todos os "calculos" do programa.
 *
 */
public class GestVendasModel implements IGestVendasModel, Serializable {
    private int vendasLidas;
    private ICatCli catCli;
    private ICatProd catProd;
    private List<IVenda> vendas;
    private IFaturas faturas;
    private IFilial[] filial;
    private IInfos infos;
    private final Crono time;
    private static final int F = 3;


    /**
     *Construtor que recebe as paths para cada um dos ficheiros.
     * @param clientes Path para o ficheiro de clientes.
     * @param produtos Path para o ficheiro de produtos.
     * @param vendas Path para o ficheiro de vendas.
     * @throws IOException Exceção para o caso das paths nao ser válida.
     */
    public GestVendasModel(String clientes, String produtos, String vendas) throws IOException {
        this.time = new Crono();
        this.infos = new Infos();
        this.infos.setClientes(clientes);
        this.infos.setProdutos(produtos);
        this.infos.setVendas(vendas);
        this.time.start();
        this.catCli = new CatCli(clientes);
        this.catProd = new CatProd(produtos);
        List<String> vendasS = new ArrayList<>();
        BufferedReader in = new BufferedReader(new FileReader(vendas));
        String linha;
        while ((linha = in.readLine()) != null) {
            vendasS.add(linha);
        }
        this.vendasLidas = vendasS.size();
        this.vendas = vendasS.parallelStream().map(Venda::new).filter(v->v.isValido(catCli,catProd)).collect(Collectors.toList());
        vendasS = null;
        this.faturas = new Faturas(catProd);
        this.filial = new Filial[3];
        for (int i = 0; i < 3; i++) {
            this.filial[i] = new Filial();
        }
        for(IVenda v:this.vendas) {
            this.filial[v.getFilial()-1] = this.filial[v.getFilial()-1].update(v);
            this.faturas = this.faturas.update(v);
        }
        this.time.stop();
    }

    /**
     * @return Tempo que o model demorou a ser inicializado.
     */
    public String getTime() {
        return this.time.getTime();
    }

    /**
     * @return Path correspondente ao ficheiro de vendas.
     */
    public String getVendasFile(){
        return this.infos.getVendas();
    }

    /**
     * @return Path correspondente ao ficheiro de clientes.
     */
    public String getClientesFile(){
        return this.infos.getClientes();
    }

    /**
     * @return Path correspondente ao ficheiro de produtos.
     */
    public String getProdutosFile(){
        return this.infos.getProdutos();
    }

    /**
     * Calcula o número de vendas inválidas que estão no ficheiro de vendas.
     * @return Numero de vendas inválidas.
     */
    public int numVendasErradas(){
        return this.vendasLidas - this.vendas.size();
    }

    /**
     * Calcula o número total de produtos lidos e validados.
     * @return Numero de produtos válidos que estão no catálogo.
     */
    public int numTotalProdutos(){
        return this.catProd.size();
    }

    /**
     * Calcula o número de produtos que foram e que não foram comprados.
     * @return Map Entry em que a key é o número de produtos comprados e value é o número de produtos não comprados.
     */
    public Map.Entry<Integer,Integer> getProdutosComprados(){
        int a = (int) this.vendas.stream().map(IVenda::getProduto).distinct().count();
        return new AbstractMap.SimpleEntry<>(a,this.catProd.size()-a);
    }
    /**
     * Calcula o número total de clientes lidos e validados.
     * @return Numero de clientes válidos que estão no catálogo.
     */
    public int numTotalClientes(){
        return this.catCli.size();
    }
    /**
     * Calcula o número de clientes compradores e não compradores.
     * @return Map Entry em que a key é o número de clientes compradores e value é o número de clientes não compradores.
     */
    public Map.Entry<Integer,Integer> getClientesCompradores(){
        int a = (int) this.vendas.stream().map(IVenda::getCliente).distinct().count();
        return new AbstractMap.SimpleEntry<>(a,this.catCli.size()-a);
    }

    /**
     * Calcula o número de vendas em que o preço é 0.0.
     * @return Número de vendas a 0.0.
     */
    public int getVendasFree(){
        return (int) this.vendas.stream().filter(a->a.getPreco() == 0).count();
    }

    /**
     * Calcula a faturação total das vendas.
     * @return Total faturado.
     */
    public double getFaturacao(){
        return this.faturas.faturacaoTotal();
    }

    /**
     * Metodo estático para se saber qual é o numero de filiais.
     * @return Numero de filiais.
     */
    public static int getF() {
        return F;
    }

    //1.2

    /**
     * Calcula o numero de vendas feitas por mês.
     * @return Map em que key corresponde ao mẽs e value corresponde ao número de vendas.
     */
    public Map<Integer,Integer> numComprasPorMes(){
        return this.vendas.stream()
                .map(IVenda::getMes)
                .collect(Collectors.toMap(Function.identity(),a->1,Integer::sum));
    }

    /**
     * Método que calcula o total faturado por mês numa certa filial.
     * @param filial Filial para a qual vai ser calculada a faturação.
     * @return Map em que a key é o mẽs e o value é a faturação.
     * @throws InvalidFilialException Exceção para caso a filial seja inválida.
     */
    public Map<Integer,Double> faturacaoTotalFilial(int filial) throws InvalidFilialException{
        if(!(filial>0 && filial<= F))
            throw new InvalidFilialException("Filial Inválido");
        return this.faturas.totalFaturadoFilial(filial);
    }

    /**
     * Método que calcula o total de clientes distintos por mês numa certa filial.
     * @param filial Filial para a qual vai ser calculada o número de clientes.
     * @return Map em que a key é o mẽs e o value é a faturação.
     * @throws InvalidFilialException Exceção para caso a filial seja inválida.
     */
    public Map<Integer,Integer> clientesPorFilial(int filial) throws InvalidFilialException {
        if(!(filial>0 && filial<= F))
            throw new InvalidFilialException("Filial Inválido");

        return this.vendas.stream()
                .filter(a->a.getFilial() == filial)
                .collect(Collectors.groupingBy(IVenda::getMes))
                .entrySet()
                .stream()
                .map(a-> new AbstractMap.SimpleEntry<>(a.getKey(),(int) a.getValue().stream().map(IVenda::getCliente).distinct().count()))
                .collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue));
    }


    //querie 1

    /**
     * Calcula a lista ordenada dos produtos que ninguém comprou.
     * @return Lista dos produtos não comprados.
     */
    public List<String> produtosNaoComprados(){
        return this.faturas.produtosNComprados();
    }

    //querie 2

    /**
     * Calcula o total de vendas efetuadas e o numero de clientes que fizeram compras num determinado mês.
     * @param mes Mês a calcular.
     * @return Map Entry em que a key é o numero total vendas e value é o numero de clientes distintos.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     */
    public Map.Entry<Integer,Integer> vendasClientesTotais(int mes) throws InvalidMesException{
        if (!(mes>=1 && mes <=12))
            throw new InvalidMesException("Mês Inválido");

        List<IVenda> aux = this.vendas.stream().filter(a->a.getMes() == mes).collect(Collectors.toList());
        return new AbstractMap.SimpleEntry<>(aux.size(),(int) aux.stream().map(IVenda::getCliente).distinct().count());
    }

    /**
     * Calcula o total de vendas efetuadas e o numero de clientes que fizeram compras num determinado mês e filial.
     * @param mes Mês a calcular.
     * @param filial Filial a calcular.
     * @return Map Entry em que a key é o numero total vendas e value é o numero de clientes distintos.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     * @throws InvalidFilialException Exceção para caso a filial seja inválida.
     */
    public Map.Entry<Integer,Integer> vendasClientesTotais(int mes,int filial) throws InvalidMesException,InvalidFilialException{
        if (!(mes>=1 && mes <=12))
            throw new InvalidMesException("Mês Inválido");
        if(!(filial>0 && filial<= F))
            throw new InvalidFilialException("Filial Inválido");

        List<IVenda> aux = this.vendas.stream().filter(a->a.getMes() == mes && a.getFilial() == filial).collect(Collectors.toList());
        return new AbstractMap.SimpleEntry<>(aux.size(),(int) aux.stream().map(IVenda::getCliente).distinct().count());
    }

    //querie 3
    /**
     * Calcula o número de compras, o número de produtos distintos e o total gasto por um certo cliente num mês.
     * @param cliente Cliente a procurar.
     * @param mes Mes onde foram feitas as compras
     * @return Map Entry em que a key é o numero de compras, o value é uma map entry onde a key é o numero de produtos distintos e o value é o total gasto.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     * @throws InvalidClienteException Exceção para caso o cliente seja inválido.
     */
    public Map.Entry<Integer,Map.Entry<Integer,Double>> infoClienteMes(String cliente,int mes) throws InvalidMesException,InvalidClienteException{
        if (!(mes>=1 && mes <=12))
            throw new InvalidMesException("Mês Inválido");
        if(!(this.catCli.existe(cliente)))
            throw new InvalidClienteException("Cliente Inválido");

        List<IVenda> aux = this.vendas.stream().filter(a->a.getMes() == mes && a.getCliente().equals(cliente)).collect(Collectors.toList());
        return new AbstractMap.SimpleEntry<>(aux.size(),
                new AbstractMap.SimpleEntry<>((int) aux.stream().map(IVenda::getProduto).distinct().count(),
                        aux.stream().mapToDouble(IVenda::totalSale).sum()));
    }

    //querie 4

    /**
     alcula o numero de clientes diferentes que compraram um determinado produto, quantas vezes foi comprado e quanto foi faturado num mes
     * @param produto Produto a procurar.
     * @param mes Mes onde foram feitas as compras
     * @return Map Entry em que a key é o numero de clientes diferentes, o value é uma map entry onde a key é o numero de vezes que foi comprado e o value é o total faturado por esse produto.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     * @throws InvalidProdutoException Exceção para caso o produto seja inválido.
     */
    public Map.Entry<Integer,Map.Entry<Integer,Double>> infoProdutoMes(String produto,int mes) throws InvalidMesException,InvalidProdutoException{
        if (!(mes>=1 && mes <=12))
            throw new InvalidMesException("Mês Inválido");
        if(!(this.catProd.existe(produto)))
            throw new InvalidProdutoException("Produto Inválido");

        List<IVenda> aux = this.vendas.stream().filter(a->a.getMes() == mes && a.getProduto().equals(produto)).collect(Collectors.toList());
        return new AbstractMap.SimpleEntry<>(aux.size(),
                new AbstractMap.SimpleEntry<>((int) aux.stream().map(IVenda::getCliente).distinct().count(),
                        aux.stream().mapToDouble(IVenda::totalSale).sum()));
    }

    //querie 5

    /**
     * Determina a lista ordenada de produtos e quantas vezes um dado cliente comprou.
     * @param cliente Cliente a procurar.
     * @return Lista de Map entry em que a key é o produto e o value é a quantidade.
     * @throws InvalidClienteException Exceção para caso o cliente seja inválido.
     */
    public List<Map.Entry<String,Integer>> produtosMaisCompradosCliente(String cliente) throws InvalidClienteException {
        if(!(this.catCli.existe(cliente)))
            throw new InvalidClienteException("Cliente Inválido");

        List<Map<String, Integer>> r = new ArrayList<>();

        for (IFilial a : this.filial)
            r.add(a.produtosCompradosCliente(cliente));

        return r.stream().filter(Objects::nonNull)
                .flatMap(a->a.entrySet().stream())
                .collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue,Integer::sum,HashMap::new))
                .entrySet()
                .stream()
                .sorted((a,b)->{
                    int i = Integer.compare(b.getValue(), a.getValue());
                    if (i == 0)
                        i = a.getKey().compareTo(b.getKey());
                    return i;
                })
                .collect(Collectors.toList());
    }


    //querie 6
    /**
     * Determina a lista ordenada de produtos(por quantidade vendida) e por quantos clientes distintos foi comprado.
     * @param n Numero de produtos a apresentar.
     * @return Lista de Map entry em que a key é o produto e o value é o número de clientes distintos.
     */
    public List<Map.Entry<String,Integer>> produtosMaisVendidos(int n){
        List<IFatura> faturas = this.faturas.getAllFatOrd();
        if(n>faturas.size()) n = faturas.size();
        faturas = faturas.subList(0,n);
        return faturas.stream().map(a-> new AbstractMap.SimpleEntry<>(a.getProduto(),a.getQuantidadeClientes())).collect(Collectors.toList());
    }


    //querie 7

    /**
     * Determina o top de clientes por filial.
     * @return Map em que a key é o filial e value é a lista ordenada com os clientes que mais compraram.
     */
    public Map<Integer,List<String>> melhoresClientesPorFilial(){
        Map<Integer,List<String>> res = new HashMap<>();
        for (int i = 0; i < F; i++) {
            res.put(i+1,this.filial[i].melhoresCompradores().subList(0,3));
        }
        return res;
    }

    //querie 8

    /**
     * Determina a lista de clientes que compraram mais produtos diferentes
     * @return Lista de Map Entry em que a key é o cliente e o value é o numero de produtos distintos comprados.
     */
    public List<Map.Entry<String,Integer>> querie8(){
        return this.vendas.stream().collect(Collectors.groupingBy(IVenda::getCliente))
                .entrySet()
                .stream()
                .map(a-> new AbstractMap.SimpleEntry<>(a.getKey(), new HashSet<>(a.getValue()).size()))
                .sorted((a, b) -> {
                    if (!a.getValue().equals(b.getValue()))
                        return -(a.getValue() - b.getValue());
                    else return a.getKey().compareTo(b.getKey());
                })
                .collect(Collectors.toList());
    }

    //querie 9

    /**
     * Determina a lista de clientes que mais compraram um dado produto e quanto gastaram no total.
     * @param produto Produto a procurar.
     * @return Lista de Map Entry ordenada por total gosto em que a key é o cliente e o value é o total gasto.
     * @throws InvalidProdutoException Exceção para caso o produto seja inválido.
     */
    public List<Map.Entry<String,Double>> querie9 (String produto) throws InvalidProdutoException{
        if(!(this.catProd.existe(produto)))
            throw new InvalidProdutoException("Produto Inválido");

        boolean flag;
        List<Map.Entry<String,Map.Entry<Integer,Double>>> aux =  new ArrayList<>();
        for(IVenda v: this.vendas){
            if(v.getProduto().equals(produto)){
                flag = false;
                for(int i = 0 ; i<aux.size() && !flag ; i++){
                    Map.Entry<String,Map.Entry<Integer,Double>> l = aux.get(i);
                    if(l.getKey().equals(v.getCliente())){
                        aux.set(i,new AbstractMap.SimpleEntry<>(l.getKey(),
                                new AbstractMap.SimpleEntry<>(l.getValue().getKey()+v.getQuantidade(),l.getValue().getValue()+v.totalSale())));
                        flag = true;
                    }
                }
                if(!flag) {
                    aux.add(new AbstractMap.SimpleEntry<>(v.getCliente(),
                            new AbstractMap.SimpleEntry<>(v.getQuantidade(),v.totalSale())));
                }
            }
        }
        return aux.stream().sorted((a,b) -> -(a.getValue().getKey() - b.getValue().getKey()))
                .map(a -> new AbstractMap.SimpleEntry<>(a.getKey(),a.getValue().getValue()))
                .collect(Collectors.toList());
    }

    //querie 10

    /**
     * Determina a faturacao de um produto por mês e filial.
     * @param prod Produto a procurar.
     * @return Map em que a key é o mês e o value é a lista com as faturacoes para cada filial.
     * @throws InvalidProdutoException Exceção para caso o produto seja inválido.
     */
    public Map<Integer,List<Double>> querie10 (String prod) throws InvalidProdutoException{
        if(!(this.catProd.existe(prod)))
            throw new InvalidProdutoException("Produto Inválido");
        Map<Integer,List<Double>> res = new HashMap<>();
        for (int i = 0; i < 12; i++) {
            List<Double> aux = new ArrayList<>();
            for (int j = 0;j<3;j++){
                aux.add(this.filial[j].getFaturacao(prod,i+1));
            }
            res.put(i+1,aux);
        }
        return res;
    }
    /**
     * Guarda o estado atual do Model para um dado ficheiro.
     * @param file Caminho do ficheiro a guardar.
     * @throws IOException Exceção de erro a escrever para o ficheiro.
     */
    public void save(String file) throws IOException{
        FileOutputStream r = new FileOutputStream(file);
        ObjectOutputStream o = new ObjectOutputStream(r);
        o.writeObject(this);
        o.flush();
        o.close();
    }

    /**
     * Carrega o Model de um ficheiro de ObjectStream
     * @param file Caminho do ficheiro a carregar
     * @return Modelo lido
     * @throws IOException Erro a ler do ficheiro.
     * @throws ClassNotFoundException O ficheiro lido é invalido.
     */
    public static GestVendasModel load(String file) throws IOException, ClassNotFoundException {
        FileInputStream r = new FileInputStream(file);
        ObjectInputStream o = new ObjectInputStream(r);
        GestVendasModel gest = (GestVendasModel) o.readObject();
        o.close();
        return gest;
    }
}
