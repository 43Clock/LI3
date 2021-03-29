package View;

import java.awt.*;
import java.util.List;

public class Navegador implements INavegador{
    private final List<String> strings;
    private final StringBuilder builder;
    private int pageSize;
    private int nCol;
    private int nPages;
    private int page;
    protected final int separador;
    private int maxPrint;

    public Navegador(List<String> strings,int linhas,int nCol){
        this.builder = new StringBuilder();
        this.strings = strings;
        this.maxPrint = 0;
        strings.forEach(a->this.maxPrint = Math.max(a.length(), this.maxPrint));
        this.separador = this.maxPrint+3;
        this.pageSize = linhas;
        this.nCol = nCol;
        this.nPages = (strings.size()%(nCol*pageSize))!=0?(strings.size()/(nCol*pageSize)):strings.size()-1;
        this.page = 0;
    }

    public void next(){
        this.page = (page+1<= nPages)?page+1:page;
    }

    public void  previous(){
        this.page = (page-1>= 0)?page-1:page;
    }

    public void setPage(int i){
        if(i <= 0) this.page = 0;
        else
            this.page = (i <=nPages)?i-1:nPages;
    }

    private String repeat(String s,int n){
        return String.valueOf(s).repeat(Math.max(0, n));
    }


    public String toString(){
        int pos, r = 0;
        builder.setLength(0);
        builder.append("Total: ").append(this.strings.size()).append("\n");
        for(int i = this.pageSize * this.page; i < this.pageSize * (this.page + 1); i++){
            for(int j = 0; j < this.nCol && j + i * this.nCol < this.strings.size(); j++){
                pos = j + i * this.nCol;
                builder.append(pos + 1).append(".");
                builder.append(repeat(" ",
                        String.valueOf(this.strings.size()).length() - String.valueOf(pos + 1).length() + 1
                ).toString());
                builder.append(this.strings.get(pos)).append(repeat(" ",this.separador));
                builder.append(repeat(" ",this.maxPrint - this.strings.get(pos).length()));

            }
            r++;
            builder.append("\n");
        }
        builder.append(repeat("\n",this.pageSize - r  + 2));
        builder.append("\t\t").append(this.page + 1).append("/").append(this.nPages+1);
        builder.append("\n (n)ext |(p)revious| page number| (b)ack\n");
        return builder.toString();
    }
}
