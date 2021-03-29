package Controller;

import Exceptions.InvalidClienteException;
import Exceptions.InvalidFilialException;
import Exceptions.InvalidMesException;
import Exceptions.InvalidProdutoException;
import Model.Crono;
import Model.GestVendasModel;
import Model.IGestVendasModel;
import View.IGestVendasView;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;


/**
 * Classe que permite a iteração de um utilizador com o programa, sendo este responsável pela gestão dos inputs feitos.
 */
public class GestVendasController implements IGestVendasController{
    private IGestVendasModel model;
    private IGestVendasView view;
    private Menu menu;

    /**
     * Construtor da Classe GestVendasController
     */
    public GestVendasController(){
        menu = Menu.Inicial;
    }

    /**
     * Setter para o model
     * @param m Model a usar.
     */
    public void setModel(IGestVendasModel m){
        this.model = m;
    }

    /**
     * Setter para o view
     * @param view View a usar
     */
    public void setView(IGestVendasView view) {
        this.view = view;
    }

    /**
     * Método que começa o controller
     */
    public void run(){
        boolean flag = true;
        String erro = "";
        view.showFirstLoad(model.getTime());
        view.askForPrints(IGestVendasView.Menu.Default);
        while(flag){
            this.view.showErro(erro);
            erro = "";
            switch(menu){
                case Exit:
                    flag = false;
                    break;
                case Inicial:
                    view.askForPrints(IGestVendasView.Menu.Inicial);
                    int i =  Input.lerInt();
                    switch(i){
                        case 1:
                            menu = Menu.Estaticas;
                            break;
                        case 2:
                            menu = Menu.Dinamicas;
                            break;
                        case 3:
                            menu = Menu.Save;
                            break;
                        case 4:
                            menu = Menu.LoadT;
                            break;
                        case 5:
                            menu = Menu.Exit;
                            break;
                        default:
                            view.askForPrints(IGestVendasView.Menu.Invalid);
                            break;
                    }
                    break;
                case Dinamicas:
                    view.askForPrints(IGestVendasView.Menu.Dinamicas);
                    i = Input.lerInt();
                    switch(i){
                        case 1:
                            menu = Menu.Q1;
                            break;
                        case 2:
                            menu = Menu.Q2;
                            break;
                        case 3:
                            menu = Menu.Q3;
                            break;
                        case 4:
                            menu = Menu.Q4;
                            break;
                        case 5:
                            menu = Menu.Q5;
                            break;
                        case 6:
                            menu = Menu.Q6;
                            break;
                        case 7:
                            menu = Menu.Q7;
                            break;
                        case 8:
                            menu = Menu.Q8;
                            break;
                        case 9:
                            menu = Menu.Q9;
                            break;
                        case 10:
                            menu = Menu.Q10;
                            break;
                        case 11:
                            menu = Menu.Inicial;
                            break;
                    }
                    break;

                case Q1:
                    Crono c1 = new Crono();
                    c1.start();
                    List<String> q1 = model.produtosNaoComprados();
                    c1.stop();
                    view.showQuerie1(q1,c1.getTime());
                    menu = Menu.Dinamicas;
                    break;
                case Q2:
                    view.askForPrints(IGestVendasView.Menu.Mes);
                    int s = Input.lerInt();
                    view.askForPrints(IGestVendasView.Menu.Filial);
                    view.askForPrints(IGestVendasView.Menu.OpcaoFilial);
                    int f = Input.lerInt();
                    Crono c = new Crono();
                    try{
                        Map.Entry<Integer, Integer> res;
                        if(f==0) {
                            c.start();
                            res = model.vendasClientesTotais(s);
                            c.stop();
                        }
                        else {
                            c.start();
                            res = model.vendasClientesTotais(s,f);
                            c.stop();
                        }
                        view.showQuerie2(res,s,f,c.getTime());
                        menu = Menu.Dinamicas;
                    }
                    catch (InvalidMesException | InvalidFilialException e){
                        erro = e.getMessage();
                    }
                    break;
                case Q3:
                    view.askForPrints(IGestVendasView.Menu.Cliente);
                    String string = Input.lerString();
                    Crono c3 = new Crono();
                    try{
                        List<Map.Entry<Integer,Map.Entry<Integer,Double>>> res = new ArrayList<>();
                        c3.start();
                        for(int j = 1; j<13; j++){
                            res.add(model.infoClienteMes(string,j));
                        }
                        c3.stop();
                        view.showQuerie3(res,string,c3.getTime());
                        menu = Menu.Dinamicas;
                    }
                    catch (InvalidMesException | InvalidClienteException e){
                        erro = e.getMessage();
                    }
                    break;
                case Q4:
                    view.askForPrints(IGestVendasView.Menu.Produto);
                    String prod= Input.lerString();
                    Crono c4 = new Crono();
                    try{
                        List<Map.Entry<Integer,Map.Entry<Integer,Double>>> res = new ArrayList<>();
                        c4.start();
                        for(int j = 1; j<13; j++){
                            res.add(model.infoProdutoMes(prod,j));
                        }
                        c4.stop();
                        view.showQuerie4(res,prod,c4.getTime());
                        menu = Menu.Dinamicas;
                    }
                    catch (InvalidMesException | InvalidProdutoException e){
                        erro = e.getMessage();
                    }
                    break;
                case Q5:
                    view.askForPrints(IGestVendasView.Menu.Cliente);
                    String cli = Input.lerString();
                    Crono c5 = new Crono();
                    try{
                        c5.start();
                        List<Map.Entry<String,Integer>> res;
                        res = model.produtosMaisCompradosCliente(cli);
                        c5.stop();
                        view.showQuerie5(res,cli,c5.getTime());
                        menu = Menu.Dinamicas;
                    }
                    catch (InvalidClienteException e){
                        erro = e.getMessage();
                    }
                    break;
                case Q6:
                    Crono c6 = new Crono();
                    view.askForPrints(IGestVendasView.Menu.NumProd);
                    int n = Input.lerInt();
                    c6.start();
                    List<Map.Entry<String,Integer>> res = model.produtosMaisVendidos(n);
                    c6.stop();
                    view.showQuerie6(res,c6.getTime());
                    menu = Menu.Dinamicas;
                    break;
                case Q7:
                    Crono c7 = new Crono();
                    c7.start();
                    Map<Integer,List<String>> res1 = model.melhoresClientesPorFilial();
                    c7.stop();
                    view.showQuerie7(res1,c7.getTime());
                    menu = Menu.Dinamicas;
                    break;
                case Q8:
                    Crono c8 = new Crono();
                    view.askForPrints(IGestVendasView.Menu.NumCli);
                    int n1 = Input.lerInt();
                    c8.start();
                    List<Map.Entry<String,Integer>> res2 = model.querie8();
                    if(n1<=res2.size())
                        res2 = res2.subList(0,n1);
                    c8.stop();
                    view.showQuerie8(res2,c8.getTime());
                    menu = Menu.Dinamicas;
                    break;
                case Q9:
                    view.askForPrints(IGestVendasView.Menu.Produto);
                    String prod1 = Input.lerString();
                    view.askForPrints(IGestVendasView.Menu.NumCli);
                    int cli1 = Input.lerInt();
                    Crono c9 = new Crono();
                    try{
                        c9.start();
                        List<Map.Entry<String,Double>> res3 = model.querie9(prod1);
                        if(cli1>res3.size()) cli1 = res3.size();
                        res3 = res3.subList(0,cli1);
                        c9.stop();
                        view.showQuerie9(res3,prod1,c9.getTime());
                        menu = Menu.Dinamicas;
                    }
                    catch (InvalidProdutoException e){
                        erro = e.getMessage();
                    }
                    break;
                case Q10:
                    view.askForPrints(IGestVendasView.Menu.Produto);
                    String prod10 = Input.lerString();
                    Crono c10 = new Crono();
                    try{
                       c10.start();
                       Map<Integer,List<Double>> res4 = model.querie10(prod10);
                       c10.stop();
                       view.showQuerie10(res4,prod10,c10.getTime());
                       menu = Menu.Dinamicas;
                    }
                    catch (InvalidProdutoException e){
                        erro = e.getMessage();
                    }
                    break;
                case Estaticas:
                    view.askForPrints(IGestVendasView.Menu.Estaticas);
                    i = Input.lerInt();
                    switch(i){
                        case 1:
                            menu = Menu.E1;
                            break;
                        case 2:
                            menu = Menu.E2;
                            break;
                        case 3:
                            menu = Menu.Inicial;
                            break;
                        default:
                            view.askForPrints(IGestVendasView.Menu.Invalid);
                            break;
                    }
                    break;

                case E1:
                    Crono ce1 = new Crono();
                    ce1.start();
                    String vendas = this.model.getVendasFile();
                    String clientes = this.model.getClientesFile();
                    String produtos = this.model.getProdutosFile();
                    int vendasInv = this.model.numVendasErradas();
                    int vendasFree = this.model.getVendasFree();
                    double fatTot = this.model.getFaturacao();
                    int totalProd = this.model.numTotalProdutos();
                    Map.Entry<Integer,Integer> prodComprados = this.model.getProdutosComprados();
                    Map.Entry<Integer,Integer> cliComp = this.model.getClientesCompradores();
                    ce1.stop();
                    List<String> rese1 = new ArrayList<>();
                    rese1.add(vendas);
                    rese1.add(clientes);
                    rese1.add(produtos);
                    rese1.add(String.valueOf(vendasInv));
                    rese1.add(String.valueOf(vendasFree));
                    rese1.add(String.format("%.2f",fatTot));
                    rese1.add(String.valueOf(totalProd));
                    rese1.add(String.valueOf(prodComprados.getKey()));
                    rese1.add(String.valueOf(prodComprados.getValue()));
                    rese1.add(String.valueOf(cliComp.getKey()));
                    rese1.add(String.valueOf(cliComp.getValue()));
                    view.showQEstatica1(rese1,ce1.getTime());
                    menu = Menu.Estaticas;
                    break;
                case E2:
                    Crono ce2 = new Crono();
                    Map<Integer,Integer> comprasMes = model.numComprasPorMes();
                    List<Map<Integer,Double>> faturacaoFilial = new ArrayList<>();
                    List<Map<Integer,Integer>> clientesFilial = new ArrayList<>();
                    ce2.start();
                    for (int j = 1;j <= GestVendasModel.getF();j++){
                        try {
                            faturacaoFilial.add(model.faturacaoTotalFilial(j));
                            clientesFilial.add(model.clientesPorFilial(j));
                        }
                        catch (InvalidFilialException ignored){}
                    }
                    ce2.stop();
                    List<List<String>> e2 = new ArrayList<>();

                    List<String> cliMes = new ArrayList<>();
                    for(int mes = 1;mes<13;mes++){
                        cliMes.add(comprasMes.get(mes).toString());
                    }
                    e2.add(cliMes);


                    for(int fil = 0;fil< GestVendasModel.getF();fil++){
                        List<String> fatFil = new ArrayList<>();
                        for(int mes = 0;mes<12;mes++){
                            fatFil.add(String.format("%.2f",faturacaoFilial.get(fil).get(mes)));
                        }
                        e2.add(fatFil);
                    }

                    for(int fil = 0;fil< GestVendasModel.getF();fil++){
                        List<String> cliFil = new ArrayList<>();
                        for(int mes = 1;mes<13;mes++){
                            cliFil.add(clientesFilial.get(fil).get(mes).toString());
                        }
                        e2.add(cliFil);
                    }
                    view.showQEstatica2(e2,ce2.getTime());
                    menu = Menu.Estaticas;
                    break;

                case Save:
                    view.askForPrints(IGestVendasView.Menu.Save);
                    try {
                        String file = Input.lerString();
                        if(file.equals("")) file = "gestVendas.dat";
                        Crono save = new Crono();
                        save.start();
                        this.model.save(file);
                        save.stop();
                        view.showTime(save.getTime());
                        menu = Menu.Inicial;
                    }
                    catch (IOException e) {erro = "Ficheiro Inválido";}
                    break;
                case LoadT:
                    view.askForPrints(IGestVendasView.Menu.LoadT);
                    int opcao = Input.lerInt();
                    switch (opcao){
                        case 1:
                            menu = Menu.LoadTxt;
                            break;
                        case 2:
                            menu = Menu.LoadData;
                            break;
                        case 3:
                            menu = Menu.Inicial;
                            break;
                        default:
                            view.askForPrints(IGestVendasView.Menu.Invalid);
                            break;
                    }
                    break;
                case LoadTxt:
                    view.askForPrints(IGestVendasView.Menu.PathClientes);
                    String clientesP = Input.lerString();
                    view.askForPrints(IGestVendasView.Menu.PathProdutos);
                    String produtosP = Input.lerString();
                    view.askForPrints(IGestVendasView.Menu.PathVendas);
                    String vendasP = Input.lerString();
                    try{
                        Crono lt = new Crono();
                        lt.start();
                        this.model = null;
                        this.model = new GestVendasModel(clientesP,produtosP,vendasP);
                        lt.stop();
                        view.showFirstLoad(lt.getTime());
                        menu = Menu.Inicial;
                    } catch (IOException e) {
                        erro = "Ficheiro(s) Invalido(s)";
                    }
                    break;
                case LoadData:
                    view.askForPrints(IGestVendasView.Menu.PathEstrutura);
                    String estruturas = Input.lerString();
                    try {
                        Crono ld = new Crono();
                        ld.start();
                        this.model = null;
                        this.model = GestVendasModel.load(estruturas);
                        ld.stop();
                        view.showFirstLoad(ld.getTime());
                        menu = Menu.Inicial;
                    } catch (IOException | ClassNotFoundException e) {
                        erro = "Ficheiro Invalido";
                    }
                    break;
            }
        }
    }
}
