SET output_format_write_statistics = 0;
SELECT DISTINCT (tutor_name) AS _1700001171315, (banke_name) AS _1700001171303, (user_id) AS _1700001171329, (is_hujing_add_wechat) AS _1700001171341, (is_activation) AS _1700001171344, (is_submit_survey) AS _1700001171345, (call_success_ucnt) AS _1700001171348 FROM `aeolus_data_db_aeolus_bp_edu_202007`.`aeolus_data_table_56294_prod` WHERE (((((p_date >= '2021-08-12') AND (p_date <= '2021-08-12')) AND ((base_name) = ('西安')) AND ((if(group_name is null ,'暂无',group_name)) = ('小中学部-西安-流量产品2部-A-4组')) AND ((concat(toString(years),'年-',term_name,'-',category_name)) = ('2021年-暑-短期班')) AND ((concat(toString(batch),'期')) = ('5期')) AND ((base_name) = ('西安'))))) LIMIT 1000  SETTINGS fallback_to_stale_replicas_for_distributed_queries=0,max_replica_delay_for_distributed_queries = 1, fallback_to_stale_replicas_for_distributed_queries=0 FORMAT JSONCompact