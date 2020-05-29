# EEG-features
A Parallel Algorithm Framework for Feature Extraction of EEG Signals on MPI
 We present a parallel framework based on MPI for a large dataset to extract power spectrum features of EEG signals
so as to improve the speed of brain signal processing. At present, the Welch method has been wildly used to estimate the power
spectrum. However, the traditional Welch method takes a lot of time especially for the large dataset. In view of this, we added the
MPI into the traditional Welch method and developed it into a reusable master-slave parallel framework. As long as the EEG data
of any format are converted into the text fle of a specifed format, the power spectrum features can be extracted quickly by this
parallel framework. In the proposed parallel framework, the EEG signals recorded by a channel are divided into N overlapping
data segments. Ten, the PSD of N segments are computed by some nodes in parallel. Te results are collected and summarized by
the master node. Te fnal PSD results of each channel are saved in the text fle, which can be read and analyzed by Microsoft Excel.
Tis framework can be implemented not only on the clusters but also on the desktop computer. In the experiment, we deploy this
framework on a desktop computer with a 4-core Intel CPU. It took only a few minutes to extract the power spectrum features from
the 2.85 GB EEG dataset, seven times faster than using Python. Tis framework makes it easy for users, who do not have any
parallel programming experience in constructing the parallel algorithms to extract the EEG power spectrum.


Usage steps:

1, Download the dataset from the URL:http://kdd.ics.uci.edu/databases/eeg/eeg.html.

2,In our research work ,we used the full data set  eeg_full.tar .

3,Preprocess the dataset .

　　　1) Uncompress all EEG fileｓ ;
   
     2) gcc get_eeg_val.c -o get_eeg_val 
     
     3) bash get_val_bat.sh
     
4,All preprocessed data can be processed  by the proposed MPI　program so that we can get the PSD features ．

　　　１) Change the  directory to welch_eeg10 
   
     2) make;#This will create a MPI progarm which can be used to extract Welch PSD  from EEG ;
     
     3) copy ./bin/xqwelch ./diaoduall.sh  to the directory  which   the  preprocessed the EEG data located in ;
     
     Users can adjust parameters according to the  number　 of　CPU coreｓ
     
     4)bash diaoduall.sh 
     


Relevant Papers:

Qi Xiong, et al"A Parallel Algorithm Framework for Feature Extraction of EEG Signals on MPI," Computational and Mathematical Methods in Medicine, vol. 2020, Article ID 9812019, 10 pages, 2020. https://doi.org/10.1155/2020/9812019.

Citation Request:

Please cite the following  article:Qi Xiong,et al "A Parallel Algorithm Framework for Feature Extraction of EEG Signals on MPI," Computational and Mathematical Methods in Medicine, vol. 2020, Article ID 9812019, 10 pages, 2020. https://doi.org/10.1155/2020/9812019.

我们为大型脑电数据集提供了一个基于MPI的并行框架，以提取脑电信号的功率谱特征，从而提高脑电信号处理的速度。目前，Welch方法已被广泛用于功率谱估计。但是，传统的Welch方法要花费大量时间，尤其是对于大型数据集。有鉴于此，我们将MPI引入到传统的Welch方法中，并将其开发为可重用的主从并行框架。只要将任何格式的EEG数据转换为指定格式的文本文件，都可以通过此并行框架快速提取功率谱特征。在提出的并行框架中，我们将每个通道记录的EEG信号划分为N个重叠的数据段，分发给一些节点并行计算这N段的PSD（功率谱密度）。主节点收集和汇总计算结果。每个通道的最终PSD结果保存在文本文件中，Microsoft Excel可以读取和分析该文件。 这个框架不仅可以在集群上实现，而且可以在台式计算机上实现。在实验中，我们将此框架部署在具有4核Intel CPU的台式计算机上。从2.85 GB EEG数据集中提取功率谱特征仅需几分钟，比使用Python快7倍。该框架简单易用，没有任何并行编程经验的用户可以轻松构建并行算法以提取EEG功率谱。


使用步骤：

1，从以下网址下载数据集：http：//kdd.ics.uci.edu/databases/eeg/eeg.html。

2，在我们的研究工作中，我们使用了完整的数据集eeg_full.tar。

3，预处理数据集。

     1) 解压所有 EEG文件 ;
     
     2) gcc get_eeg_val.c -o get_eeg_val 
     
     3) bash get_val_bat.sh
     
4,All preprocessed data can be processed  by the proposed MPI　program so that we can get the PSD features ．

　　　１) 改变目录到 welch_eeg10 
   
     2) make;#这将创建一个MPI程序，可用于从EEG中提取Welch PSD;
     
     3) copy ./bin/xqwelch ./diaoduall.sh  目录（此目录用来存放已经预处理好的脑电数据）用户可以根据自己电脑的ＣＰＵ的核数情况来调整参数。
     
     4)bash diaoduall.sh 
     

相关论文：

Qi Xiong, et al "A Parallel Algorithm Framework for Feature Extraction of EEG Signals on MPI," Computational and Mathematical Methods in Medicine, vol. 2020, Article ID 9812019, 10 pages, 2020. https://doi.org/10.1155/2020/9812019.

引用论文：

Qi Xiong,et al "A Parallel Algorithm Framework for Feature Extraction of EEG Signals on MPI," Computational and Mathematical Methods in Medicine, vol. 2020, Article ID 9812019, 10 pages, 2020. https://doi.org/10.1155/2020/9812019.
