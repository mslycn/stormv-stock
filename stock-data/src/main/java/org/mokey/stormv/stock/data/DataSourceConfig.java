package org.mokey.stormv.stock.data;

import com.alibaba.druid.pool.DruidDataSource;
import org.apache.ibatis.session.SqlSessionFactory;
import org.mybatis.spring.SqlSessionFactoryBean;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import javax.sql.DataSource;

@Configuration
@MapperScan(basePackages = "org.mokey.stormv.stock.data.dao")
public class DataSourceConfig {

	@Value("${spring.datasource.url}")
	private String url;
	
	@Value("${spring.datasource.driver-class-name}")
	private String driverClass;

	@Bean
	public DataSource dataSource() {
		DruidDataSource ds = new DruidDataSource();

		ds.setDriverClassName(driverClass);
		ds.setUrl(url);

		return ds;
	}

	@Bean
	public SqlSessionFactory sqlSessionFactory(DataSource dataSource)
			throws Exception {
		final SqlSessionFactoryBean sessionFactory = new SqlSessionFactoryBean();
		sessionFactory.setDataSource(dataSource);
		return sessionFactory.getObject();
	}
}
