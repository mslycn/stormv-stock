package org.mokey.stormv.stock.data;

import org.mokey.stormv.stock.data.dao.KLineDao;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.PropertySource;
import org.springframework.context.support.PropertySourcesPlaceholderConfigurer;

/**
 * Created by enousei on 9/24/15.
 */
@SpringBootApplication
@ComponentScan("org.mokey.stormv.stock")
@PropertySource(value = "classpath:application.properties")
public class Application {
    public static void main(String[] args){
        ApplicationContext context =
                new AnnotationConfigApplicationContext(Application.class);
        try{
            KLineDao dao = context.getBean(KLineDao.class);
            Integer has = dao.createTable("abc");

            System.out.println(has);

        }catch (Exception e){
            e.printStackTrace();
        }

    }

    @Bean
    public static PropertySourcesPlaceholderConfigurer placeHolderConfigurer() {
        return new PropertySourcesPlaceholderConfigurer();
    }
}
