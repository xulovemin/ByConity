SET output_format_write_statistics = 0;
SELECT (concat(toString(batch),'期')) AS _1700001171335, (base_name) AS _1700001171325, (leader_name) AS _1700001171321, (tutor_name) AS _1700001171315, (count(distinct if(is_hujing_add_wechat=1,order_id,null))/(count(distinct order_id))) AS _1700001172020, (count(distinct if(is_activation=1,order_id,null))/count(distinct order_id)) AS _1700001171817, (count(distinct if(call_success_ucnt>0,order_id,null))/(count(distinct order_id))) AS _1700001172091 FROM `aeolus_data_db_aeolus_bp_edu_202007`.`aeolus_data_table_56294_prod` WHERE (((((p_date >= '2021-08-12') AND (p_date <= '2021-08-12')) AND ((concat(toString(years),'年-',term_name,'-',category_name)) = ('2021年-暑-长期班')) AND (if(group_name is null ,'暂无',group_name) NOT LIKE '%LPC%') AND ((base_name) IN (('武汉'), ('西安'), ('长春'))) AND ((concat(toString(batch),'期')) = ('3期')) AND ((grade_name) IN (('8年级'), ('9年级'))) AND ((subject_name_list) IN (('语文'), ('数学'), ('英语'), ('物理'), ('化学')))))) GROUP BY concat(toString(batch),'期'), base_name, leader_name, tutor_name ORDER BY _1700001171335 ASC LIMIT 1000  SETTINGS fallback_to_stale_replicas_for_distributed_queries=0,max_replica_delay_for_distributed_queries = 1, fallback_to_stale_replicas_for_distributed_queries=0 FORMAT JSONCompact